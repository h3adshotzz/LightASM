# LightASM Memory address space

This document will outline how the memory address space will work in LightASM. Memory addresses are required for two things. The first being values that can be manipulated with commands and stored in registers, the seccond being branching and skipping to a different section of code. I will outline the plan for both here and try to come up with a universal solution. 

## The Idea

LightASM has the `memory` structs, `address_page_t` and `address_space_t`. My new idea is to alter the two in the following way.

Instead of using one `address_space_t` to store both the users data and the commands address, there will be two. the struct will use this format:
```c
typedef struct address_space_t {
    space_type type;
    void** pages;
    int elements;
    int allocated;
} address_page_t;
```
With `space_type` having either the `SPACE_TYPE_VAL` or `SPACE_TYPE_NODE` `space_type`, and the `pages` being an array of `void`'s. `allocated` and `elements` are used to keep track of how many elements memory is allocated for, and how many are actually in the array respectively.

The process of creating a new address space should involve asking for a `space_type`, which should throw an error if not a val or node. Then, different things will be done depending on `space_type`.

But, firstly, we create a new `address_space_t` and `malloc` enough memory. 

### `SPACE_TYPE_VAL`

If the `space_type` is a value, the we set allocated to 128, the max amount of memory given to the user, then elements to 0 as there aren't currently any elements. We then `malloc(sizeof(int) * allocated)` to have a sufficent amount of memory for the 128 elements. There will be a function to check the amount of elements and remove any that exceed the allocated limit. 

Once that is done, we return the newly created address space.

### `SPACE_TYPE_NODE`

If the type is a node, then we again set allocated, however only to 10. We adjust allocated by 1 each time a command is added. elements is started at 0. Again, we have to allocated actual memory, which would be done by `malloc(sizeof(node) * 10)`. The reset would work like a value, however this does require some changes to the node struct, which are shown here: 
```c
typedef struct node {
    node_type node;
    void* value;
+   int memory_ref; 
} node;
```
We add an integer called `memory_ref`. This is used to show it's position in the address space and so we can handle the command.


## Handling commands

First and foremost, when `run_console()` is called, we create two `address_space_t`'s. One for the user data and one for the nodes. Then, every time a function that returns an `interpreter_result_t` (which is usually functions that are interpreting a node), we add that node to the nodes address space. 

### Accessing user data.

When a call to a function is made that want's to access user data, we also parse the appropriate address space. We can then find the value at the appropriate address and use it for the command given.

### Acessing nodes

When a call, such as `BRANCH`, is made, we parse the appropriate address space and `ln_pos`. We then take the address given in the node, and set `ln_pos` to the position that the node at the given address is in the `nodearray`.

## Some Notes
I may realise some flaws with this plan, I came up with it at 4 in the morning. They'll be fixed in due course. If you have any usggestions please make a pull request. 