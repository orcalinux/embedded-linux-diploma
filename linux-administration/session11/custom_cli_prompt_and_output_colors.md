# Customizing CLI Prompt and Output Colors in Bash and C/C++

This README provides step-by-step instructions on how to customize the colors of your command-line interface (CLI) prompt in **Bash** and how to output colored text in **C/C++** programs. Whether you're looking to enhance the aesthetics of your terminal or make your program's output more readable, this guide covers the essentials.

---

## Table of Contents

- [Customizing CLI Prompt and Output Colors in Bash and C/C++](#customizing-cli-prompt-and-output-colors-in-bash-and-cc)
  - [Table of Contents](#table-of-contents)
  - [Changing Bash Prompt Colors](#changing-bash-prompt-colors)
    - [Understanding `PS1`](#understanding-ps1)
    - [Using ANSI Escape Codes](#using-ansi-escape-codes)
      - [Common Color Codes](#common-color-codes)
    - [Example: Colored Prompt](#example-colored-prompt)
    - [Persisting Changes](#persisting-changes)
    - [Customizing Prompt with Git Information](#customizing-prompt-with-git-information)
      - [Benefits](#benefits)
      - [Prerequisites](#prerequisites)
      - [Steps to Customize Prompt with Git Information](#steps-to-customize-prompt-with-git-information)
      - [Using Existing Tools for Enhanced Git Prompts](#using-existing-tools-for-enhanced-git-prompts)
      - [Tips for Customizing Git Prompts](#tips-for-customizing-git-prompts)
  - [Coloring Output in C/C++](#coloring-output-in-cc)
    - [Using ANSI Escape Codes in C/C++](#using-ansi-escape-codes-in-cc)
    - [Example: Colored Output in C](#example-colored-output-in-c)
    - [Example: Colored Output in C++](#example-colored-output-in-c-1)
    - [Handling Cross-Platform Compatibility](#handling-cross-platform-compatibility)
  - [ANSI Color Codes Table](#ansi-color-codes-table)
    - [Foreground (Text) Colors](#foreground-text-colors)
    - [Background Colors](#background-colors)
    - [Additional Text Attributes](#additional-text-attributes)
    - [Combining Multiple Codes](#combining-multiple-codes)
    - [256-Color and True Color (24-bit) Support](#256-color-and-true-color-24-bit-support)
      - [256-Color Mode](#256-color-mode)
      - [True Color (24-bit)](#true-color-24-bit)
    - [Full Example: Combining Attributes and Colors in Bash](#full-example-combining-attributes-and-colors-in-bash)
    - [Usage in C/C++](#usage-in-cc)
  - [Quick Reference: Common ANSI Escape Sequences](#quick-reference-common-ansi-escape-sequences)
  - [Additional Tips](#additional-tips)
  - [Resources](#resources)

---

## Changing Bash Prompt Colors

### Understanding `PS1`

In Bash, the prompt is defined by the `PS1` environment variable. By customizing `PS1`, you can change the appearance of your terminal prompt, including adding colors.

### Using ANSI Escape Codes

Colors in the terminal are achieved using ANSI escape codes. The general format for setting colors is:

```
\[\e[<COLOR_CODE>m\]
```

After setting the color, you should reset it to default using:

```
\[\e[0m\]
```

#### Common Color Codes

| Color        | Code |
| ------------ | ---- |
| Black        | 30   |
| Red          | 31   |
| Green        | 32   |
| Yellow       | 33   |
| Blue         | 34   |
| Magenta      | 35   |
| Cyan         | 36   |
| White        | 37   |
| Bright Black | 90   |
| Bright Red   | 91   |
| ...          | ...  |

_Note: You can also use background colors by adding 10 to the foreground color codes (e.g., Background Red is `41`)._

### Example: Colored Prompt

Here's an example of how to set a colored prompt:

```bash
export PS1="\[\e[32m\]\u@\h\[\e[0m\]:\[\e[34m\]\w\[\e[0m\]\$ "
```

**Explanation:**

-   **`\[\e[32m\]`** – _Sets the text color to **green** for the section following it._

    -   `\e` – Escape character.
    -   `[32m` – ANSI code for green.
    -   `\[` and `\]` – Wraps non-printing characters to ensure correct cursor positioning during line wrapping.

-   **`\u`** – _Displays the **current username** (e.g., `sarah`)._

-   **`@`** – _Literal `@` character, separating the username and hostname (e.g., `sarah@`)._

-   **`\h`** – _Displays the **hostname** up to the first `.` (e.g., `linux`)._

-   **`\[\e[0m\]`** – _Resets text color to the **default terminal color** after the hostname._

    -   `[0m` – ANSI code to reset all styles.

-   **`:`** – _Literal colon `:` used as a separator (e.g., `sarah@linux:`)._

-   **`\[\e[34m\]`** – _Sets the text color to **blue** for the working directory._

    -   `[34m` – ANSI code for blue.

-   **`\w`** – _Displays the **current working directory** relative to the home directory (e.g., `~/embedded-linux-diploma`)._

    -   The `~` indicates the home directory.

-   **`\[\e[0m\]`** –  _Resets the color to **default** after displaying the working directory._

-   **`\$`** – _Displays the shell prompt symbol:_
    -   `$` – For regular users.
    -   `#` – If the effective user ID (`UID`) is `0` (root).
-   **` ` (Space at the end)** –  _Adds a space after the prompt for readability._

### Persisting Changes

To make the changes permanent, add the `export PS1=...` line to your `~/.bashrc` or `~/.bash_profile` file:

1. Open the file in a text editor, e.g., `vim ~/.bashrc`.
2. Add the `export PS1=...` line at the end of the file.
3. Save and exit the editor.
4. Reload the configuration with `source ~/.bashrc` or restart the terminal.

### Customizing Prompt with Git Information

Enhancing your Bash prompt to include Git repository information can significantly improve your workflow by providing immediate context about your current Git branch and status. Here's how to integrate Git details into your prompt.

#### Benefits

-   **Immediate Feedback:** Know which branch you're on without running additional commands.
-   **Status Indicators:** Optionally show if there are uncommitted changes.
-   **Enhanced Navigation:** Easily identify the repository context in nested directories.

#### Prerequisites

-   **Git Installed:** Ensure Git is installed on your system. You can verify by running `git --version`.
-   **Bash Shell:** This guide assumes you're using Bash. Adjustments may be needed for other shells like Zsh.

#### Steps to Customize Prompt with Git Information

1. **Define a Function to Retrieve Git Information**

    Add the following function to your `~/.bashrc` or `~/.bash_profile`:

    ```bash
    # Function to extract Git branch name
    function parse_git_branch() {
        git branch 2>/dev/null | grep '*' | sed 's/* //'
    }

    # Function to check if the directory is a Git repository
    function is_git_repo() {
        git rev-parse --is-inside-work-tree > /dev/null 2>&1
    }
    ```

2. **Modify `PS1` to Include Git Information**

    Update your `PS1` to incorporate the Git branch when inside a Git repository. Here's an example with colors:

    ```bash
    export PS1="\[\e[32m\]\u@\h:\w\[\e[34m\]\$(if is_git_repo; then echo ' (git: '$(parse_git_branch)')'; fi)\$ \[\e[0m\]"
    ```

    **Explanation:**

    - `\[\e[32m\]`: Sets the main prompt color to green.
    - `\u@\h:\w`: Displays `username@hostname:current_directory`.
    - `\[\e[34m\]`: Changes color to blue for Git information.
    - `\$(...)`: Executes the enclosed commands:
        - `if is_git_repo; then ... fi`: Checks if the current directory is a Git repository.
        - `echo ' (git: '$(parse_git_branch)')'`: If inside a Git repo, appends the current branch name.
    - `\$`: Displays `$` or `#` based on user privileges.
    - `\[\e[0m\]`: Resets the color to default.

    **Result:** When inside a Git repository, the prompt might look like this:

    ```
    user@hostname:/path/to/repo (git: main)$
    ```

    The Git branch information appears in blue, distinguishing it from the rest of the prompt.

3. **Enhancing Git Status Indicators (Optional)**

    To further enhance the prompt, you can include indicators for uncommitted changes or other Git statuses. Here's an advanced example:

    ```bash
    # Function to get Git status
    function git_status() {
        if is_git_repo; then
            STATUS=$(git status --porcelain 2>/dev/null)
            if [ -n "$STATUS" ]; then
                echo "✗"
            else
                echo "✓"
            fi
        fi
    }

    export PS1="\[\e[32m\]\u@\h:\w\[\e[34m\]\$(if is_git_repo; then echo ' ('$(parse_git_branch)')'; fi)\[\e[31m\]\$(git_status)\[\e[32m\]\$ \[\e[0m\]"
    ```

    **Explanation:**

    - `git_status` function checks for uncommitted changes:
        - Displays a red `✗` if there are changes.
        - Displays a green `✓` if the working directory is clean.
    - The prompt includes:
        - Username, hostname, and directory in green.
        - Git branch in blue.
        - Git status indicator (`✗` or `✓`) in red.
        - Command prompt symbol `$` in green.

    **Result:** Your prompt might look like:

    ```
    user@hostname:/path/to/repo (main)✗$
    ```

    Where `✗` indicates there are uncommitted changes.

4. **Reload Your Shell Configuration**

    After making changes to your `~/.bashrc` or `~/.bash_profile`, reload the configuration:

    ```bash
    source ~/.bashrc
    ```

    Or restart your terminal.

#### Using Existing Tools for Enhanced Git Prompts

Manually customizing the prompt provides flexibility, but there are also tools and frameworks that offer more advanced Git prompt features with minimal setup:

-   **[git-prompt.sh](https://github.com/git/git/blob/master/contrib/completion/git-prompt.sh):** A script provided by Git to enhance your prompt with Git information.

    **Usage:**

    1. **Download `git-prompt.sh`:**

        ```bash
        wget https://raw.githubusercontent.com/git/git/master/contrib/completion/git-prompt.sh -O ~/.git-prompt.sh
        ```

    2. **Source the Script and Customize `PS1`:**

        Add the following to your `~/.bashrc`:

        ```bash
        source ~/.git-prompt.sh

        export PS1="\[\e[32m\]\u@\h:\w\[\e[33m\]\$(__git_ps1 ' (%s)')\$ \[\e[0m\]"
        ```

        **Explanation:**

        - `__git_ps1 ' (%s)'`: Inserts the current Git branch in parentheses if inside a Git repository.
        - Colors:
            - Main prompt: green.
            - Git branch: yellow.

-   **[Oh My Bash](https://github.com/ohmybash/oh-my-bash):** A community-driven framework for managing your Bash configuration with themes and plugins, including Git prompt enhancements.

    **Installation:**

    ```bash
    sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmybash/oh-my-bash/master/tools/install.sh)"
    ```

    **Usage:**

    -   Choose a theme that includes Git information (e.g., `bobby`).
    -   Customize further by editing `~/.bashrc` as needed.

-   **[Powerline](https://github.com/powerline/powerline):** A status line plugin that can be used with various shells to provide a rich and informative prompt, including Git details.

    **Installation:**

    Follow the [Powerline installation guide](https://powerline.readthedocs.io/en/latest/installation.html) for your specific system.

#### Tips for Customizing Git Prompts

-   **Color Consistency:** Use colors that are easily distinguishable and maintain readability against your terminal background.
-   **Minimalism vs. Information:** Balance the amount of information displayed to avoid clutter. Include only what’s necessary for your workflow.
-   **Symbols and Icons:** Incorporate symbols (like `✓` and `✗`) to represent Git statuses succinctly.
-   **Performance Considerations:** Complex prompt functions can slow down your terminal. Optimize scripts or use efficient tools to minimize lag.

---

## Coloring Output in C/C++

To output colored text in C or C++ programs, you can use ANSI escape codes, similar to how it's done in Bash. Here's how to implement it:

### Using ANSI Escape Codes in C/C++

ANSI escape codes can be embedded directly into strings to change the color of the text output to the terminal.

### Example: Colored Output in C

```c
#include <stdio.h>

int main() {
    // Define color codes
    const char *RED = "\033[31m";
    const char *GREEN = "\033[32m";
    const char *YELLOW = "\033[33m";
    const char *RESET = "\033[0m";

    printf("%sThis is red text.%s\n", RED, RESET);
    printf("%sThis is green text.%s\n", GREEN, RESET);
    printf("%sThis is yellow text.%s\n", YELLOW, RESET);

    return 0;
}
```

**Explanation:**

-   `\033[31m`: Sets the text color to red.
-   `\033[32m`: Sets the text color to green.
-   `\033[33m`: Sets the text color to yellow.
-   `\033[0m`: Resets the text color to default.

### Example: Colored Output in C++

```cpp
#include <iostream>

int main() {
    // Define color codes
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string RESET = "\033[0m";

    std::cout << RED << "This is red text." << RESET << std::endl;
    std::cout << GREEN << "This is green text." << RESET << std::endl;
    std::cout << YELLOW << "This is yellow text." << RESET << std::endl;

    return 0;
}
```

**Explanation:**

Same as the C example, but using C++'s `std::cout` for output.

### Handling Cross-Platform Compatibility

**Windows Consideration:**

-   On Windows, especially older versions, the terminal may not support ANSI escape codes by default.
-   **Windows 10 and later**: Supports ANSI escape codes in the terminal, but you might need to enable it programmatically.

**Enabling ANSI Codes in Windows (C++ Example):**

```cpp
#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>

int main() {
#ifdef _WIN32
    // Enable ANSI escape codes on Windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    // Define color codes
    const std::string RED = "\033[31m";
    const std::string RESET = "\033[0m";

    std::cout << RED << "This is red text." << RESET << std::endl;

    return 0;
}
```

**Explanation:**

-   The `#ifdef _WIN32` block ensures that the code to enable ANSI processing is only compiled on Windows.
-   `EnableVirtualTerminalProcessing` allows the Windows terminal to interpret ANSI escape codes.

---

## ANSI Color Codes Table

### Foreground (Text) Colors

| Color              | Code | Description                              |
| ------------------ | ---- | ---------------------------------------- |
| **Reset**          | 0    | Resets all attributes                    |
| **Bold**           | 1    | Increases text brightness                |
| **Underline**      | 4    | Underlines the text                      |
| **Blink**          | 5    | Makes text blink                         |
| **Reverse**        | 7    | Inverts foreground and background colors |
| **Hidden**         | 8    | Hides the text                           |
| **Default**        | 39   | Default foreground color                 |
| **Black**          | 30   | Sets text color to black                 |
| **Red**            | 31   | Sets text color to red                   |
| **Green**          | 32   | Sets text color to green                 |
| **Yellow**         | 33   | Sets text color to yellow                |
| **Blue**           | 34   | Sets text color to blue                  |
| **Magenta**        | 35   | Sets text color to magenta               |
| **Cyan**           | 36   | Sets text color to cyan                  |
| **White**          | 37   | Sets text color to white                 |
| **Bright Black**   | 90   | Sets text color to bright black (Gray)   |
| **Bright Red**     | 91   | Sets text color to bright red            |
| **Bright Green**   | 92   | Sets text color to bright green          |
| **Bright Yellow**  | 93   | Sets text color to bright yellow         |
| **Bright Blue**    | 94   | Sets text color to bright blue           |
| **Bright Magenta** | 95   | Sets text color to bright magenta        |
| **Bright Cyan**    | 96   | Sets text color to bright cyan           |
| **Bright White**   | 97   | Sets text color to bright white          |

### Background Colors

| Color              | Code | Description                                  |
| ------------------ | ---- | -------------------------------------------- |
| **Default**        | 49   | Default background color                     |
| **Black**          | 40   | Sets background color to black               |
| **Red**            | 41   | Sets background color to red                 |
| **Green**          | 42   | Sets background color to green               |
| **Yellow**         | 43   | Sets background color to yellow              |
| **Blue**           | 44   | Sets background color to blue                |
| **Magenta**        | 45   | Sets background color to magenta             |
| **Cyan**           | 46   | Sets background color to cyan                |
| **White**          | 47   | Sets background color to white               |
| **Bright Black**   | 100  | Sets background color to bright black (Gray) |
| **Bright Red**     | 101  | Sets background color to bright red          |
| **Bright Green**   | 102  | Sets background color to bright green        |
| **Bright Yellow**  | 103  | Sets background color to bright yellow       |
| **Bright Blue**    | 104  | Sets background color to bright blue         |
| **Bright Magenta** | 105  | Sets background color to bright magenta      |
| **Bright Cyan**    | 106  | Sets background color to bright cyan         |
| **Bright White**   | 107  | Sets background color to bright white        |

### Additional Text Attributes

| Attribute         | Code | Description                              |
| ----------------- | ---- | ---------------------------------------- |
| **Reset All**     | 0    | Resets all text attributes               |
| **Bold**          | 1    | Makes text bold                          |
| **Dim**           | 2    | Makes text dim                           |
| **Italic**        | 3    | Makes text italic                        |
| **Underline**     | 4    | Underlines the text                      |
| **Blink**         | 5    | Makes text blink                         |
| **Inverse**       | 7    | Inverts foreground and background colors |
| **Hidden**        | 8    | Hides the text                           |
| **Strikethrough** | 9    | Adds a strikethrough to the text         |

### Combining Multiple Codes

You can combine multiple ANSI codes by separating them with semicolons (`;`). For example, to make text bold and red:

```bash
\033[1;31m
```

**Example in Bash:**

```bash
echo -e "\033[1;31mThis is bold red text.\033[0m"
```

**Example in C:**

```c
#include <stdio.h>

int main() {
    printf("\033[1;31mThis is bold red text.\033[0m\n");
    return 0;
}
```

### 256-Color and True Color (24-bit) Support

For terminals that support 256 colors or True Color (24-bit), you can use the following extended codes:

#### 256-Color Mode

-   **Syntax:**

    -   Foreground: `\033[38;5;<color_code>m`
    -   Background: `\033[48;5;<color_code>m`

-   **Example:**

    ```bash
    echo -e "\033[38;5;82mThis is a green text using 256-color.\033[0m"
    ```

#### True Color (24-bit)

-   **Syntax:**

    -   Foreground: `\033[38;2;<r>;<g>;<b>m`
    -   Background: `\033[48;2;<r>;<g>;<b>m`

-   **Example:**

    ```bash
    echo -e "\033[38;2;255;165;0mThis is orange text using True Color.\033[0m"
    ```

**Note:** True Color support depends on the terminal emulator being used. Most modern terminals support it, but some older ones may not.

### Full Example: Combining Attributes and Colors in Bash

```bash
# Bold Green Text
echo -e "\033[1;32mThis is bold green text.\033[0m"

# Underlined Blue Text with Yellow Background
echo -e "\033[4;34;43mUnderlined blue text on yellow background.\033[0m"

# Bright Magenta Text
echo -e "\033[95mThis is bright magenta text.\033[0m"

# 256-Color Example
echo -e "\033[38;5;208mThis is orange text using 256-color.\033[0m"

# True Color Example
echo -e "\033[38;2;75;0;130mThis is indigo text using True Color.\033[0m"
```

### Usage in C/C++

**C Example:**

```c
#include <stdio.h>

int main() {
    // Bold Red Text
    printf("\033[1;31mThis is bold red text.\033[0m\n");

    // Underlined Blue Text with Yellow Background
    printf("\033[4;34;43mUnderlined blue text on yellow background.\033[0m\n");

    // Bright Magenta Text
    printf("\033[95mThis is bright magenta text.\033[0m\n");

    // 256-Color Example
    printf("\033[38;5;208mThis is orange text using 256-color.\033[0m\n");

    // True Color Example
    printf("\033[38;2;75;0;130mThis is indigo text using True Color.\033[0m\n");

    return 0;
}
```

**C++ Example:**

```cpp
#include <iostream>

int main() {
    // Bold Red Text
    std::cout << "\033[1;31mThis is bold red text.\033[0m" << std::endl;

    // Underlined Blue Text with Yellow Background
    std::cout << "\033[4;34;43mUnderlined blue text on yellow background.\033[0m" << std::endl;

    // Bright Magenta Text
    std::cout << "\033[95mThis is bright magenta text.\033[0m" << std::endl;

    // 256-Color Example
    std::cout << "\033[38;5;208mThis is orange text using 256-color.\033[0m" << std::endl;

    // True Color Example
    std::cout << "\033[38;2;75;0;130mThis is indigo text using True Color.\033[0m" << std::endl;

    return 0;
}
```

---

## Quick Reference: Common ANSI Escape Sequences

| Action                       | Code Sequence  | Example Usage                                 |
| ---------------------------- | -------------- | --------------------------------------------- |
| Reset All Attributes         | `\033[0m`      | `echo -e "\033[0mReset Text"`                 |
| Bold Text                    | `\033[1m`      | `echo -e "\033[1mBold Text\033[0m"`           |
| Underline Text               | `\033[4m`      | `echo -e "\033[4mUnderlined Text\033[0m"`     |
| Red Text                     | `\033[31m`     | `echo -e "\033[31mRed Text\033[0m"`           |
| Green Background             | `\033[42m`     | `echo -e "\033[42mGreen Background\033[0m"`   |
| Bright Yellow Text           | `\033[93m`     | `echo -e "\033[93mBright Yellow Text\033[0m"` |
| Reset and Set Bold Blue Text | `\033[0;1;34m` | `echo -e "\033[0;1;34mBold Blue Text\033[0m"` |

**Note:** Always reset the attributes after applying them to prevent them from affecting subsequent text.

---

## Additional Tips

-   **Combining Multiple Attributes:** You can combine multiple attributes by separating their codes with semicolons (`;`). For example, to make text bold and underlined:

    ```bash
    echo -e "\033[1;4mBold and Underlined Text\033[0m"
    ```

-   **Testing Your Colors:** To see all 256 colors in your terminal, you can run the following Bash script:

    ```bash
    for i in {0..255}; do
        printf "\033[38;5;%sm %3d " "$i" "$i"
        if (( (i + 1) % 16 == 0 )); then
            printf "\n"
        fi
    done
    printf "\033[0m\n"
    ```

-   **Using Variables for Readability:** In scripts or programs, define variables for colors to make your code more readable and maintainable.

    **Bash Example:**

    ```bash
    # Define color variables
    RED="\033[31m"
    GREEN="\033[32m"
    YELLOW="\033[33m"
    BLUE="\033[34m"
    RESET="\033[0m"

    # Use the variables
    echo -e "${RED}This is red text.${RESET}"
    echo -e "${GREEN}This is green text.${RESET}"
    echo -e "${YELLOW}This is yellow text.${RESET}"
    echo -e "${BLUE}This is blue text.${RESET}"
    ```

    **C++ Example:**

    ```cpp
    #include <iostream>
    #include <string>

    int main() {
        // Define color variables
        const std::string RED = "\033[31m";
        const std::string GREEN = "\033[32m";
        const std::string YELLOW = "\033[33m";
        const std::string BLUE = "\033[34m";
        const std::string RESET = "\033[0m";

        // Use the variables
        std::cout << RED << "This is red text." << RESET << std::endl;
        std::cout << GREEN << "This is green text." << RESET << std::endl;
        std::cout << YELLOW << "This is yellow text." << RESET << std::endl;
        std::cout << BLUE << "This is blue text." << RESET << std::endl;

        return 0;
    }
    ```

---

## Resources

-   **Bash Prompt Customization:**

    -   [Bash Prompt HOWTO](https://tldp.org/HOWTO/Bash-Prompt-HOWTO/)
    -   [Wikipedia: ANSI Escape Code](https://en.wikipedia.org/wiki/ANSI_escape_code#Colors)

-   **C/C++ Colored Output:**

    -   [ANSI Escape Code on C++ Reference](https://en.cppreference.com/w/cpp/io/c/fprintf)
    -   [C++ Console Colors](https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal)

-   **Cross-Platform Libraries:**

    -   [Boost::IOStreams](https://www.boost.org/doc/libs/1_75_0/doc/html/boost_io.html)
    -   [termcolor](https://github.com/ikalnytskyi/termcolor) – A C++ library for printing colored messages.

-   **Git Prompt Tools:**
    -   [git-prompt.sh](https://github.com/git/git/blob/master/contrib/completion/git-prompt.sh)
    -   [Oh My Bash](https://github.com/ohmybash/oh-my-bash)
    -   [Powerline](https://github.com/powerline/powerline)
