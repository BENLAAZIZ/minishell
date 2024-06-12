# minishell

In our extensive and critical project within the 42 network, we are tasked with developing a sophisticated command interpreter that emulates the functionality of bash. This minishell will manage environment variables, launch programs, and handle their return values. Additionally, it will include several built-in functions such as **`cd`**, **`echo`**, **`env`**, **`exit`**, **`export`**, **`pwd`**, and **`unset`**. This ambitious and lengthy endeavor is a cornerstone of our curriculum, reflecting the depth and complexity expected in our training.

## builtin functions 


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
2. **chdir()**
The chdir() function is used to change the current working directory to the directory specified in its argument.

####  **Syntax**
```
int chdir(const char *path);
```
####  **Parameters**
+ **`path`**: A pointer to a string containing the path to the directory to which you want to change.
####  **Return Value**
On success, chdir() returns 0.
On failure, it returns -1, and errno is set to indicate the error.

#### Example
```
#include <stdio.h>
#include <unistd.h>

int main() {
    const char *newDir = "/path/to/new/dir";

    if (chdir(newDir) == 0) {
        printf("Directory changed to: %s\n", newDir);
    } else {
        perror("chdir() error");
    }
    return 0;
}
```

### `env` and `export` with no options or arguments:


In Bash, an **`environment`** refers to a set of variables that are used by the operating system to control the behavior of processes. These environment variables can store information such as user preferences, system configurations, and other settings that programs can access to tailor their functionality. Here’s a detailed explanation of environment variables in Bash and their typical use cases:


**Environment Variables in Bash**
1. Definition and Structure:

* Environment variables are key-value pairs, where the key is the variable name and the value is the variable's data.
* They are typically written in uppercase letters (e.g., PATH, HOME, USER).
2. Common Environment Variables:

* `PATH`: Specifies the directories in which the shell looks for executable files. For example, when you type a command, Bash searches these directories to find the command.
* `HOME`: Indicates the current user's home directory.
* `USER`: Contains the username of the current user.
* `SHELL`: Indicates the path to the current user's shell.
* `PWD`: Stores the current working directory.
  
**Using Environment Variables**

1. **Setting Environment Variables:**

  * You can set an environment variable using the **`export`** command:
    ```bash
    export VAR_NAME="value"
    ```
  * For example:
    ```bash
    export PATH="/usr/local/bin:$PATH"
    ```
2. **Accessing Environment Variables:**

  * To access the value of an environment variable, you can use the $ symbol followed by the variable name:
    ```bash
    echo $HOME
    ```
3. **This will print the value of the HOME environment variable.
Listing Environment Variables:**


  * You can list all environment variables using the env or printenv command:
    ```bash
    env
    ```
  * This will display all the environment variables and their values.
4. **Unsetting Environment Variables:**

  * To remove an environment variable, you can use the unset command:
    ```bash
    unset VAR_NAME
    ```
  * For example:
    ```bash
    unset PATH
    ```
5. **Using Environment Variables in Scripts:**
    * Environment variables can be used within shell scripts to make them more flexible and dynamic:
    ```bash
    #!/bin/bash
    echo "Home directory: $HOME"
    echo "Current user: $USER"
    ```
    * This script prints the home directory and current user by accessing the respective environment variables.

 ### Understanding the export Command
1. Purpose of `export`:

* The primary purpose of export is to create environment variables or modify existing ones so that they are inherited by any subsequently executed commands or child processes.
* 
2. Syntax:

      ```bash
       export VARIABLE_NAME=value
       ```
   * **`VARIABLE_NAME`** is the name of the variable you want to set.
     * **`value`** is the data you want to assign to the variable.
### How export Works
1. Setting a New Environment Variable:

    * When you create a new environment variable with export, it becomes available to all child processes started from that shell.
    ```bash
    export MY_VAR="Hello, World!"
    ```
   * Now, any command or script run from this shell can access MY_VAR.
2. Modifying an Existing Environment Variable:

    * If an environment variable already exists, you can change its value with export.
    ```bash
    export PATH="/usr/local/bin:$PATH"
    ```
  * This example prepends /usr/local/bin to the existing PATH variable, ensuring that binaries in /usr/local/bin are found before others in the search path.
3. Making a Shell Variable an Environment Variable:

    * A variable declared without export is a shell variable, local to the current shell session.
    ```bash
    MY_VAR="Hello"
    export MY_VAR
     ```
This converts MY_VAR into an environment variable.
