# minishell

# execution functions 


## echo with option -n
## `cd` with only a relative or absolute path

* In C, the functions **`getcwd()`** and **`chdir()`** are used to get and change the current working directory, respectively. These functions are part of the POSIX standard and are commonly used in Unix-like operating systems, including Linux.

1. **getcwd()**
The getcwd() function is used to get the current working directory. It copies an absolute pathname of the current working directory to the buffer provided by the user.

####  **Syntax**
```
char *getcwd(char *buf, size_t size);
```
####  **Parameters**
  
+ **`buf`**: A pointer to an array where the path name will be stored.
+ **`size`**: The size of the array pointed to by buf.
####  **Return Value**
On success, getcwd() returns a pointer to the buffer buf.
On failure, it returns NULL, and errno is set to indicate the error.


#### Example

```Copier le code
#include <stdio.h>
#include <unistd.h>
#include <limits.h>  // For PATH_MAX

int main() {
    char buf[PATH_MAX];

    if (getcwd(cwd, sizeof(buf)) != NULL) {
        printf("Current working dir: %s\n", buf);
    } else {
        perror("getcwd() error");
    }

    return 0;
}
```
