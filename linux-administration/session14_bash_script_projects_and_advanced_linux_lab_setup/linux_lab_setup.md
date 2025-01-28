# Linux Lab Environment Setup

## Table of Contents

- [Linux Lab Environment Setup](#linux-lab-environment-setup)
  - [Table of Contents](#table-of-contents)
  - [Goal](#goal)
  - [A Word About Downloads](#a-word-about-downloads)
  - [Notes to Windows Users](#notes-to-windows-users)
    - [Do Not Use or Enable Hyper-V for This Class (Windows Users Only)](#do-not-use-or-enable-hyper-v-for-this-class-windows-users-only)
    - [Antivirus Software Compatibility (Windows Users Only)](#antivirus-software-compatibility-windows-users-only)
    - [Enable Virtualization Support for Your Processor (Windows and Linux Users)](#enable-virtualization-support-for-your-processor-windows-and-linux-users)
    - [Upgrade PowerShell (Windows 7 Users Only)](#upgrade-powershell-windows-7-users-only)
  - [Instructions](#instructions)
    - [Install an SSH Client (Windows Users Only)](#install-an-ssh-client-windows-users-only)
      - [Install Git](#install-git)
    - [Install Vagrant Dependencies (Windows Users Only)](#install-vagrant-dependencies-windows-users-only)
    - [Install VirtualBox (All Users)](#install-virtualbox-all-users)
    - [Install Vagrant (All Users)](#install-vagrant-all-users)
    - [Start a Command Line Session (All Users)](#start-a-command-line-session-all-users)
    - [Add a Box to Vagrant](#add-a-box-to-vagrant)
    - [Create a Working Folder](#create-a-working-folder)
    - [Change into the Working Folder](#change-into-the-working-folder)
    - [Create a Vagrant Project Folder](#create-a-vagrant-project-folder)
    - [Create Your First Vagrant Project](#create-your-first-vagrant-project)
    - [Create Your First Virtual Machine](#create-your-first-virtual-machine)
    - [Troubleshooting](#troubleshooting)
    - [Confirm That It's Running](#confirm-that-its-running)
    - [Connect to the Virtual Machine](#connect-to-the-virtual-machine)
    - [Stop the Virtual Machine](#stop-the-virtual-machine)
    - [Start the Virtual Machine Again](#start-the-virtual-machine-again)
  - [Change the Virtual Machine's Name](#change-the-virtual-machines-name)
    - [Assign the Virtual Machine an IP Address](#assign-the-virtual-machine-an-ip-address)
    - [Destroy the Virtual Machine](#destroy-the-virtual-machine)
  - [Final Vagrantfile for `testbox01`](#final-vagrantfile-for-testbox01)
  - [Create Another Vagrant Project with Multiple Virtual Machines](#create-another-vagrant-project-with-multiple-virtual-machines)
    - [Stop the Virtual Machines](#stop-the-virtual-machines)

## Goal

The goal of this project is to create a local Linux lab environment. Once you have the environment configured, you can quickly and easily create and destroy Linux virtual machines on your Windows, Mac, or Linux computer. You will be creating new Linux systems throughout this course using the tools you will install and configure in this exercise.

## A Word About Downloads

Throughout this course, I'm going to ask you to download various pieces of software from [http://mirror.linuxtrainingacademy.com/](http://mirror.linuxtrainingacademy.com/). This way, I can ensure we are all using the same versions and getting the same results. Since other websites are not under my control, they can change their addresses and download options at any time without my knowledge. Using a website under my control prevents any problems with acquiring the required software for this course.

With that said, I've also included an "Internet download location" for each piece of software so you know where to download it in the future after you have completed this class. You can use those locations when you are deploying systems in your work or home environments. I cannot guarantee those public Internet links will always be live and accurate; however, they should point you in the right direction.

## Notes to Windows Users

### Do Not Use or Enable Hyper-V for This Class (Windows Users Only)

In this class, you are going to use Vagrant to manage virtual machines running under VirtualBox. Because VirtualBox is incompatible with Hyper-V, you will need to make sure Hyper-V is disabled. This should only be an issue if you are running a Windows **_Server_** installation.

### Antivirus Software Compatibility (Windows Users Only)

Some Windows antivirus software, such as Avira, has been known to interfere with the operation of VirtualBox. If you get an error when starting a Virtual Machine, try disabling your antivirus software. Some errors that indicate an antivirus conflict include:

-   `Error in supR3HardenedWinReSpawm`
-   `VERR_OPEN_FAILED`
-   `E_FAIL (0x80004005)`
-   `NtCreateFile(\Device\VBoxDrvStub) failed.`

### Enable Virtualization Support for Your Processor (Windows and Linux Users)

Make sure you have VT-x (for Intel processors) or AMD-V (for AMD processors) enabled in your physical computer's BIOS. This varies from manufacturer to manufacturer, so you might have to look up the documentation for your specific computer. Many computers have these options enabled by default, but some do not. If virtualization support is not enabled, you may encounter an error inside your virtual machines like:

```
This kernel requires an x86-64 CPU, but only detected an i686 CPU
```

### Upgrade PowerShell (Windows 7 Users Only)

If the `vagrant up` command hangs without producing any output and you are running Windows 7, upgrade your version of PowerShell to at least version 4.0.

## Instructions

### Install an SSH Client (Windows Users Only)

SSH, Secure Shell, is the network protocol used to connect to Linux systems. By default, Windows doesn't include an SSH client. Mac and Linux do, so Mac and Linux users should skip this step.

#### Install Git

To get an SSH client on Windows, you can install Git. Git is used for version control, but we're interested in the SSH client that it ships with. Download Git [here](http://mirror.linuxtrainingacademy.com/git/windows/).

**Internet download location:** [https://git-scm.com/download/win](https://git-scm.com/download/win)

1. Start the installer.
2. Be sure to select **"Use Git and optional Unix tools from The Windows Command Prompt"** when presented with the option. Otherwise, use the defaults.
3. If you're asked for an administrator user and password, be sure to enter it.

![Git Installation Screen](https://github.com/yourusername/yourrepo/blob/main/images/git-installation.png?raw=true)
_Figure 1: Git Installer - Select "Use Git and optional Unix tools from The Windows Command Prompt"_

_Replace the image URL with the actual path to your Git installation screenshot._

### Install Vagrant Dependencies (Windows Users Only)

Vagrant requires the **"Microsoft Visual C++ 2010 SP1 Redistributable Package (x86)"** to be installed if you are running Windows. Download it from [here](https://www.microsoft.com/en-us/download/details.aspx?id=8328). Start the installer and accept the defaults to complete the installation.

### Install VirtualBox (All Users)

1. Download VirtualBox from [http://mirror.linuxtrainingacademy.com/virtualbox/](http://mirror.linuxtrainingacademy.com/virtualbox/).
    - **Windows Users:** Download from the `windows` subdirectory.
    - **Mac Users:** Download from the `mac` subdirectory.
    - **RedHat or CentOS Users:** Download from the `centos` directory.

**Internet download location:** [https://www.virtualbox.org/wiki/Downloads](https://www.virtualbox.org/wiki/Downloads)

2. Install the software on your local machine, accepting all the defaults.
3. If prompted, enter your administrator username and password.
4. Reboot your system if requested by the installer.

### Install Vagrant (All Users)

1. Download Vagrant from [http://mirror.linuxtrainingacademy.com/vagrant/](http://mirror.linuxtrainingacademy.com/vagrant/).
    - **Windows Users:** Download from the `windows` subdirectory.
    - **Mac Users:** Download from the `mac` subdirectory.
    - **RedHat or CentOS Users:** Download from the `centos` directory.

**Internet download location:** [https://www.vagrantup.com/downloads.html](https://www.vagrantup.com/downloads.html)

2. Install the software on your local machine, accepting all the defaults.
3. If prompted, enter your administrator username and password.
4. Reboot your system if requested by the installer.

### Start a Command Line Session (All Users)

First, start a command line session on your local machine.

-   **Windows Users:**
    1. Click the **Start** button.
    2. In the Search box, type **"Command Prompt"**.
    3. In the list of results, double-click **Command Prompt**.
-   **Mac Users:** Start the **Terminal** application located in the `/Applications/Utilities` folder.
-   **Linux Users:** Start your favorite terminal emulator (e.g., GNOME Terminal, Konsole, xterm).

### Add a Box to Vagrant

A "box" in Vagrant is an operating system image. The `vagrant box add` command will download and store that box on your local system. You only need to download a box once, as this image will be cloned when you create a new virtual machine with Vagrant using the box's name.

I created a box specifically for this class and uploaded it to the public Vagrant box catalog. Run the following command on your local machine to download it:

```bash
vagrant box add jasonc/centos7
```

**Format:** `vagrant box add USER/BOX`

There are several public boxes available to download. You can search for boxes [here](https://app.vagrantup.com/boxes/search), but be sure to use the `jasonc/centos7` box for this class.

### Create a Working Folder

When the Command Prompt (Windows) or the Terminal (Mac/Linux) is launched, you will be placed in your home directory.

-   **Windows Example:** `C:\Users\jason`
-   **Mac Example:** `/Users/jason`
-   **Linux Example:** `/home/jason`

Create a folder to keep your coursework in:

```bash
mkdir shellclass
```

### Change into the Working Folder

Move into the folder you just created:

```bash
cd shellclass
```

### Create a Vagrant Project Folder

Vagrant uses the concept of projects. A Vagrant project must consist of a folder and a Vagrant configuration file, called a `Vagrantfile`. Start by creating a `testbox01` folder:

```bash
mkdir testbox01
```

### Create Your First Vagrant Project

To create the Vagrant configuration file (`Vagrantfile`), run the `vagrant init <BOX_NAME>` command. Be sure to be in the Vagrant project directory you just created and use the `jasonc/centos7` box you downloaded earlier.

```bash
cd testbox01
vagrant init jasonc/centos7
```

### Create Your First Virtual Machine

The first time you run the `vagrant up` command, Vagrant will import (clone) the Vagrant box into VirtualBox and start it. If Vagrant detects that the virtual machine already exists in VirtualBox, it will simply start it. By default, when the virtual machine is started, it is started in headless mode, meaning there is no UI for the machine visible on your local host machine.

Let's bring up your first virtual machine running Linux with Vagrant:

```bash
vagrant up
```

### Troubleshooting

On some systems, you may see the following message, though it is rare:

```
Timed out while waiting for the machine to boot. This means that
Vagrant was unable to communicate with the guest machine within
the configured ("config.vm.boot_timeout" value) time period.
If you look above, you should be able to see the error(s) that
Vagrant had when attempting to connect to the machine. These errors
are usually good hints as to what may be wrong.
If you're using a custom box, make sure that networking is properly
working and you're able to connect to the machine. It is a common
problem that networking isn't set up properly in these boxes.
Verify that authentication configurations are also set up properly,
as well.
If the box appears to be booting properly, you may want to increase
the timeout ("config.vm.boot_timeout") value.
```

If you see that message, it most likely means the virtual machine started with its networking interface disabled. To force the network interface to be enabled, you'll need to update the `Vagrantfile`. The `Vagrantfile` controls the behavior and settings of the virtual machine. Open it with your favorite text editor. You may need to use the File Explorer (Windows) or the Finder (Mac) to navigate to the folder and then open it with your desired editor.

**Tip:** [Atom](https://atom.io/) is a nice text editor that works on Mac, Windows, and even Linux. You can download it for free at [Atom.io](https://atom.io/).

Add the following lines somewhere after `Vagrant.configure(2) do |config|` and before `end`. A good place could be right after the `config.vm.box = "jasonc/centos7"` line:

```ruby
config.vm.provider "virtualbox" do |vb|
  vb.customize ['modifyvm', :id, '--cableconnected1', 'on']
end
```

Reboot the virtual machine with Vagrant:

```bash
vagrant reload
```

### Confirm That It's Running

Start the VirtualBox application.

-   **Windows Users:** Double-click the **"Oracle VM VirtualBox"** icon on your desktop.
-   **Mac Users:** Start the `/Applications/VirtualBox` application.
-   **Linux Users:** Find the application in your menuing system.

Confirm that you see a virtual machine running. It will start with the name of your Vagrant project folder.

You can also use the `vagrant status` command to check the status of the virtual machine. Confirm that it shows the virtual machine is in a **running** state:

```bash
vagrant status
```

### Connect to the Virtual Machine

SSH, Secure Shell, is the network protocol used to connect to Linux systems. Vagrant provides a nice shortcut to SSH into the virtual machine.

```bash
vagrant ssh
```

Now you are connected to the Linux virtual machine as the `vagrant` user. This default `vagrant` account is used to connect to the Linux system. For your convenience, the Vagrant application takes care of the details that allow you to connect to the box over SSH without a password.

-   **Password for `vagrant` account:** `vagrant`
-   **Password for `root` account:** `vagrant`

The `vagrant` user has full `sudo` (administrative) privileges that allow you to further configure the system. You will learn more about accounts, privileges, and `sudo` later in this course.

After running `vagrant ssh`, you should be presented with a prompt that looks similar to this:

![SSH Prompt](https://github.com/yourusername/yourrepo/blob/main/images/ssh-prompt.png?raw=true)
_Figure 2: SSH Prompt after `vagrant ssh`_

_Replace the image URL with the actual path to your SSH prompt screenshot._

You'll be working a lot at the Linux command line in this course. For now, let's log out of the Linux system by running the `exit` command.

```bash
exit
```

### Stop the Virtual Machine

The `vagrant halt` command shuts down the virtual machine. When you run this command, you will not lose any work you've performed on the virtual machine. The virtual machine will still exist in VirtualBox; it will simply be stopped.

```bash
vagrant halt
```

Open the VirtualBox application and verify that the virtual machine is still defined yet stopped.

### Start the Virtual Machine Again

Remember, to start the virtual machine, run `vagrant up`. This time, when you run the command, it will not need to import the box image into VirtualBox as the virtual machine already exists.

```bash
vagrant up
```

Open the VirtualBox application and verify that the virtual machine is now running.

## Change the Virtual Machine's Name

The `Vagrantfile` controls the behavior and settings of the virtual machine. Open it with your favorite text editor. You may need to use the File Explorer (Windows) or the Finder (Mac) to navigate to the folder and then open it with your desired editor.

**Tip:** [Atom](https://atom.io/) is a nice text editor that works on Mac, Windows, and even Linux. You can download it for free at [Atom.io](https://atom.io/).

Add the following line somewhere after `Vagrant.configure(2) do |config|` and before `end`. A good place could be right after the `config.vm.box = "jasonc/centos7"` line:

```ruby
config.vm.hostname = "testbox01"
```

Be sure to save your changes.

At this point, you could run `vagrant halt` followed by `vagrant up` to activate this change. However, Vagrant provides a shortcut: `vagrant reload`, which restarts the virtual machine, loads the new `Vagrantfile` configuration, and starts the virtual machine again. Give it a go:

```bash
vagrant reload
```

Connect to the virtual machine to confirm that its hostname has changed:

```bash
vagrant ssh
```

You should see a prompt similar to this one containing the hostname that you configured:

![Hostname Prompt](https://github.com/yourusername/yourrepo/blob/main/images/hostname-prompt.png?raw=true)
_Figure 3: Hostname Prompt after `vagrant reload`_

_Replace the image URL with the actual path to your hostname prompt screenshot._

Disconnect from the virtual machine:

```bash
exit
```

### Assign the Virtual Machine an IP Address

During this course, you are going to create virtual machines that will be able to communicate with each other as well as your local workstation. Let's give this virtual machine the IP address of `10.9.8.7`. To do that, insert the following line of configuration into the `Vagrantfile`. Remember, it needs to be inserted somewhere after `Vagrant.configure(2) do |config|` and before `end`.

```ruby
config.vm.network "private_network", ip: "10.9.8.7"
```

Save your changes.

Reload the virtual machine and let Vagrant assign the IP address to it:

```bash
vagrant reload
```

Test the connection by pinging the virtual machine.

-   **Windows Users:**

    ```bash
    ping 10.9.8.7
    ```

-   **Mac and Linux Users:**

    ```bash
    ping -c 3 10.9.8.7
    ```

The `ping` command is one simple way to test network connectivity. If you see replies, then you can safely assume the IP address is reachable and the host is up. If you see "timeout" messages, then the system is not answering your ping requests. In the "real world," this doesn't necessarily mean the system is "down." It means it is not answering your ping requests, which could be for a variety of reasons. However, for our purposes here, if you get "timeout" messages, then you can assume this system is down or something is wrong.

The first thing to try is to simply reboot the VM by running:

```bash
vagrant reload
```

If the `ping` command fails again, double-check the contents of the `Vagrantfile`, paying special attention to the `config.vm.network` line. Make any necessary changes, restart the virtual machine, and try again.

**Final Step:** Reboot the host operating system (i.e., your physical computer). This troubleshooting step primarily applies to Windows users.

### Destroy the Virtual Machine

If you're done with the virtual machine or you want to start over with a fresh copy of the virtual machine, run `vagrant destroy`.

```bash
vagrant destroy
```

It will prompt you to confirm that you want to delete the virtual machine. Answer **"y"**. If the virtual machine is running, it will stop it and then delete it. If it's already stopped, it will simply delete it.

## Final Vagrantfile for `testbox01`

Here are the contents of the `shellclass/testbox01/Vagrantfile` file with all the comments removed:

```ruby
Vagrant.configure(2) do |config|
  config.vm.box = "jasonc/centos7"
  config.vm.hostname = "testbox01"
  config.vm.network "private_network", ip: "10.9.8.7"
end
```

## Create Another Vagrant Project with Multiple Virtual Machines

Let's create another Vagrant Project and two virtual machines.

1. **Return to the `shellclass` Directory:**

    The `cd ..` command changes to the parent directory, which is represented by `..`.

    ```bash
    cd ..
    ```

2. **Create the Vagrant Project Folder and Change into That Folder:**

    ```bash
    mkdir multitest
    cd multitest
    ```

3. **Initialize the Vagrant Project:**

    This step creates the `Vagrantfile`.

    ```bash
    vagrant init jasonc/centos7
    ```

4. **Add Two Virtual Machine Definitions:**

    The first host definition will define the `test1` VM with a hostname of `"test1"` and an IP address of `10.9.8.5`. The second host definition will define the `test2` VM with a hostname of `"test2"` and an IP address of `10.9.8.6`.

    **Contents of `shellclass/multitest/Vagrantfile`:**

    ```ruby
    Vagrant.configure("2") do |config|
      config.vm.box = "jasonc/centos7"

      config.vm.define "test1" do |test1|
        test1.vm.hostname = "test1"
        test1.vm.network "private_network", ip: "10.9.8.5"
      end

      config.vm.define "test2" do |test2|
        test2.vm.hostname = "test2"
        test2.vm.network "private_network", ip: "10.9.8.6"
      end
    end
    ```

5. **Start the Virtual Machines:**

    Run the `vagrant up` command. If you do not specify a VM name, all the defined VMs will be started.

    ```bash
    vagrant up
    ```

6. **Check Their Status:**

    ```bash
    vagrant status
    ```

7. **Connect to the `test1` Virtual Machine to Confirm It's Working and Then Exit It:**

    ```bash
    vagrant ssh test1
    exit
    ```

8. **Connect to the `test2` Virtual Machine to Confirm It's Working. While logged into the `test2` VM, ping the `test1` VM to prove that the two virtual machines can communicate with each other over the network:**

    ```bash
    vagrant ssh test2
    ping -c 3 10.9.8.5
    ```

    **Note:** When you brought up the virtual machines, you may have noticed a message similar to this:

    ```
    ==> test2: Mounting shared folders...
        test2: /vagrant => /Users/jason/shellclass/multitest
    ```

    You can access the files in the Vagrant project directory that resides on your local machine inside the virtual machine. The Vagrant project directory is mounted, or shared, via the `/vagrant` directory. The only file in our local directory is the `Vagrantfile`. You can look at the file from within the VM by running the following commands while you're still logged into the `test2` VM:

    ```bash
    ls /vagrant
    cat /vagrant/Vagrantfile
    ```

9. **Exit Out of the `test2` VM:**

    ```bash
    exit
    ```

### Stop the Virtual Machines

In upcoming projects, you'll be working more with Vagrant, virtual machines, IP addresses, and more. Feel free to explore the Linux system if you'd like. (Connect by running `vagrant ssh [VM_NAME]` within the project folder.) When you're ready to stop or take a break, halt the virtual machine. Remember, you can always pick up where you left off as long as you don't destroy the virtual machine.

```bash
vagrant halt
```
