# Add Local User Script

This document explains how to create a shell script named **`add-local-user.sh`** that automates adding new user accounts on a Linux system.

---

## Table of Contents

- [Add Local User Script](#add-local-user-script)
  - [Table of Contents](#table-of-contents)
  - [Goal](#goal)
  - [Scenario](#scenario)
  - [Shell Script Requirements](#shell-script-requirements)
  - [Create a Virtual Machine](#create-a-virtual-machine)
  - [Configure the Virtual Machine](#configure-the-virtual-machine)
  - [Start the Virtual Machine and Log into It](#start-the-virtual-machine-and-log-into-it)
  - [Navigate to the /vagrant Directory](#navigate-to-the-vagrant-directory)
  - [Write the Shell Script](#write-the-shell-script)
  - [Test Your Script](#test-your-script)
    - [Accounts to Create](#accounts-to-create)
    - [Set Executable Permissions](#set-executable-permissions)
    - [Example Run of the Script](#example-run-of-the-script)
    - [Verify Account Creation](#verify-account-creation)
    - [Password Change on First Login](#password-change-on-first-login)
    - [Test Non-Superuser Execution](#test-non-superuser-execution)
  - [Reference Material](#reference-material)
    - [Vagrantfile for localusers](#vagrantfile-for-localusers)
    - [Pseudocode](#pseudocode)

---

## Goal

The goal of this exercise is to create a shell script that adds users to the same Linux system where the script is executed.

---

## Scenario

Imagine that you're working as a Linux System Administrator for a fast-growing company. The latest company initiative requires you to build and deploy dozens of servers. You're falling behind schedule and will miss your deadline for these new deployments because you are constantly being interrupted by the help desk. They keep calling you to create new Linux accounts for all the people in the company who have been recruited to test out the company's newest Linux-based application.

To meet your deadline and keep your sanity, you decide to write a shell script that will create new user accounts. Once you're done, you can put the help desk in charge of creating new accounts, allowing you to work uninterrupted and complete your server deployments on time.

---

## Shell Script Requirements

You think about what the shell script must do and how you would like it to operate. You come up with the following list:

1. **Is named** `add-local-user.sh`.
2. **Enforces** that it be executed with superuser (root) privileges. If the script is not executed with superuser privileges, it will not attempt to create a user and returns an exit status of `1`.
3. **Prompts** the person who executed the script to enter:
    - The username (login)
    - The name of the person who will be using the account
    - The initial password for the account
4. **Creates** a new user on the local system with the input provided by the user.
5. **Informs** the user if the account was not able to be created for some reason. If the account is not created, the script is to return an exit status of `1`.
6. **Displays** the username, password, and host where the account was created. This way the help desk staff can copy the output of the script to easily deliver the information to the new account holder.

After coming up with your list, you realize that you're not sure where to get the hostname information. You decide to wait until you start writing your shell script to check the bash man page to see if there are any built-in commands or variables that could provide this information.

You decide to develop your script on a Linux virtual machine running on your local operating system. This way, you can test the script's functionality before uploading it to the server where it will be used by the help desk staff.

---

## Create a Virtual Machine

First, start a command line session on your local machine. Next, move into the working folder you created for this course.

```bash
cd shellclass
```

Initialize the vagrant project using the usual process of creating a directory, changing into that directory, and running `vagrant init`. We'll name this vagrant project **`localusers`**.

```bash
mkdir localusers
cd localusers
vagrant init jasonc/centos7
```

---

## Configure the Virtual Machine

Edit the **Vagrantfile** and set the hostname of the virtual machine to **`localusers`**.

```ruby
config.vm.hostname = "localusers"
```

---

## Start the Virtual Machine and Log into It

Now you're ready to start the VM and connect to it:

```bash
vagrant up
vagrant ssh
```

---

## Navigate to the /vagrant Directory

Inside the VM, navigate to the `/vagrant` directory:

```bash
cd /vagrant
```

> **Note:** The `/vagrant` directory is shared with your local `localusers` folder, making it easy to edit files on your host machine and have them immediately available in the VM.

---

## Write the Shell Script

At this point, you can either create the script **inside** the virtual machine using `vim`, `nano`, or `emacs`, **or** you can create the file using your favorite text editor on your local operating system (such as [Atom](https://atom.io)).

When creating your script, refer back to the **Shell Script Requirements**. If you want or need more detailed steps to help you write your script, refer to the **Pseudocode** section at the end of this document. It was intentionally placed at the end to encourage you to write the script on your own. It’s fine if you need the pseudocode — as you get more scripting practice, you'll be able to write scripts without additional aids.

---

## Test Your Script

Once you've finished writing the script, test it by creating the following accounts:

### Accounts to Create

-   **Username:** `einstein`

    -   **Real Name:** Albert Einstein
    -   **Password:** `E=mc2theory$`

-   **Username:** `isaac`

    -   **Real Name:** Isaac Newton
    -   **Password:** `@ppleFell1666`

-   **Username:** `tedison`
    -   **Real Name:** Thomas Edison
    -   **Password:** `Light.Bulb1`

### Set Executable Permissions

Remember that the first time you execute the script, you’ll need to ensure it has executable permissions:

```bash
chmod 755 add-local-user.sh
```

### Example Run of the Script

_(Portions typed by the user are in **bold**.)_

```bash
sudo ./add-local-user.sh
```

> Enter the username to create: **einstein**
> Enter the name of the person or application that will be using this account: **Albert Einstein**
> Enter the password to use for the account: **E=mc2theory$**

```bash
Changing password for user einstein.
passwd: all authentication tokens updated successfully.
Expiring password for user einstein.
passwd: Success
```

> username: **einstein**
> password: **E=mc2theory$**
> host: **localusers**

### Verify Account Creation

Make sure the accounts have been created by examining the last 3 lines of the `/etc/passwd` file:

```bash
cat /etc/passwd
root:x:0:0:root:/root:/bin/bash
... # additional accounts will be displayed
einstein:x:1001:1001:Albert Einstein:/home/einstein:/bin/bash
isaac:x:1002:1002:Isaac Newton:/home/isaac:/bin/bash
tedison:x:1003:1003:Thomas Edison:/home/tedison:/bin/bash
```

> **Note:** You could also use `tail -3 /etc/passwd` to display just the last three lines of the file.

### Password Change on First Login

Switch to the `einstein` user. Because the script forces a password change upon first login, create a new password for the `einstein` user.
_(Suggested password: "CrazyHair!")_

```bash
su - einstein
```

After changing the password, exit out of the session to return to the `vagrant` user:

```bash
exit
```

### Test Non-Superuser Execution

Test to make sure that the script exits with a non-zero exit status if the user does not use superuser (root) privileges:

```bash
./add-local-user.sh
Please run with sudo or as root.
echo ${?}
1
```

---

## Reference Material

### Vagrantfile for localusers

Here are the contents of the `shellclass/localusers/Vagrantfile` file with all the comments removed:

```ruby
Vagrant.configure(2) do |config|
  config.vm.box = "jasonc/centos7"
  config.vm.hostname = "localusers"
end
```

### Pseudocode

You can use the following pseudocode to help you with the logic and flow of your script:

```plaintext
# Make sure the script is being executed with superuser privileges.
# Get the username (login).
# Get the real name (contents for the description field).
# Get the password.
# Create the user with the password.
# Check to see if the useradd command succeeded.
# Set the password.
# Check to see if the passwd command succeeded.
# Force password change on first login.
# Display the username, password, and the host where the user was created.
```
