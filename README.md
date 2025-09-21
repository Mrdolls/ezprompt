# ezprompt

`ezprompt` is a small C library that provides a simple and portable interface for creating interactive prompts with history and arrow key support.
It is designed to be easily integrated into projects such as `mini-shells`, `REPLs`, or `command-line` tools.

---

## Features

- Customizable prompt creation.

- Character-by-character user input reading.

- Built-in history management:

  - Each validated input is automatically added to the history.

  - Navigation using the arrow keys ↑ and ↓.

- Input buffer clearing after processing.

- Utility functions included (ft_strdup, ft_strlen, etc.).

---

## Usage Example

Here’s a simple example of a mini-shell using ezprompt:

```c
#include "ezprompt.h"

int main(void)
{
    t_prompt *p;

    p = calloc(1, sizeof(t_prompt));                   // → Allocate the t_prompt structure
    if (!p)                                            // → Check allocation failure
        return (1);

    if (init_prompt(p, "myshell> "))                  // → Initialize the prompt with "myshell> "
        return (1);

    while (!p->exit_flag)                              // → Main loop (runs until exit)
    {
        if (next_read(p))                              // → Read a user line (with key handling)
            break;

        if (!is_empty(p->input))                       // → Check that the input is not empty
            printf("You typed: %s\n", p->input);      // → Print the typed text

        if (clear_input(p))                            // → Clear the input buffer for the next line
            break;
    }

    free_prompt(p);                                    // → Free all allocated memory
    return (0);
}
```

---

## Example Output
```
myshell> ls -la
You typed: ls -la

myshell> echo hello
You typed: echo hello

myshell> exit
You typed: exit
```
