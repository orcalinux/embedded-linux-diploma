# **Comprehensive Demo of File Permissions, Special Bits, and User/Group Management**

## **Scenario Overview**

In this demonstration, we will simulate a scenario involving two project groups: `projA` and `projB`. We will:

- **Create Users and Groups:** Establish groups and assign users to these groups, including primary and supplementary memberships.
- **Manage Permissions:** Apply standard permission bits (`r`, `w`, `x`) and special permission bits (`setuid`, `setgid`, `sticky bit`) to files and directories.
- **Demonstrate Access Control:** Show how different users interact with files and directories based on their group memberships and assigned permissions.
- **Utilize Numeric and Symbolic Modes:** Use both numeric (octal) and symbolic representations for setting permissions.
- **Explore ACLs and Extended Attributes:** Briefly demonstrate Access Control Lists (ACLs) and extended file attributes.

**Note:** All commands requiring administrative privileges should be executed with `sudo`. Ensure you have the necessary permissions before proceeding.

---

## **Users and Groups**

### **Groups to be Created**

- `projA`
- `projB`

### **Users to be Created**

| Username  | Primary Group | Supplementary Groups |
| --------- | ------------- | -------------------- |
| `alice`   | `projA`       | _None_               |
| `bob`     | `projA`       | _None_               |
| `charlie` | `projB`       | _None_               |
| `dave`    | `projB`       | `projA`              |

_This setup allows us to observe access differences for users solely in one group versus those in multiple groups._

---

## **Step-by-Step Demonstration**

### **1. Create Groups**

First, create the necessary project groups.

```bash
sudo groupadd projA
sudo groupadd projB
```

_Verify group creation:_

```bash
getent group projA
getent group projB
```

### **2. Create Users and Assign Groups**

Create users with specified primary and supplementary group memberships.

```bash
# Create alice and bob in projA
sudo useradd -m -s /bin/bash -g projA alice
sudo useradd -m -s /bin/bash -g projA bob

# Create charlie in projB
sudo useradd -m -s /bin/bash -g projB charlie

# Create dave in projB and add to projA as supplementary
sudo useradd -m -s /bin/bash -g projB dave
sudo usermod -aG projA dave

# Set passwords for all users (you will be prompted to enter passwords)
sudo passwd alice
sudo passwd bob
sudo passwd charlie
sudo passwd dave
```

_Verification:_

```bash
id alice
# Output: uid=1001(alice) gid=1001(projA) groups=1001(projA)

id bob
# Output: uid=1002(bob) gid=1001(projA) groups=1001(projA)

id charlie
# Output: uid=1003(charlie) gid=1002(projB) groups=1002(projB)

id dave
# Output: uid=1004(dave) gid=1002(projB) groups=1002(projB),1001(projA)
```

---

### **3. Create a Project Directory and Set Permissions**

We will create a shared directory `/shared` accessible to `projA` members.

```bash
sudo mkdir /shared
```

#### **Set Group Ownership to `projA` and Default Permissions**

```bash
sudo chown :projA /shared
sudo chmod 770 /shared
# Permissions: rwx for owner (root), rwx for group (projA), --- for others
```

_Explanation:_

- **Owner (`root`):** Read, write, execute.
- **Group (`projA`):** Read, write, execute.
- **Others:** No permissions.

**Access Control:**

- `alice` and `bob` (in `projA`) can read, write, and enter `/shared`.
- `charlie` (in `projB`) cannot access `/shared`.
- `dave` (in both `projB` and `projA`) can access `/shared` through his supplementary membership in `projA`.

#### **Check Access**

- **As `alice`:**

  ```bash
  su - alice
  ls /shared    # Should be accessible
  touch /shared/alice_file.txt
  ls -l /shared/alice_file.txt
  exit
  ```

- **As `charlie`:**

  ```bash
  su - charlie
  ls /shared
  # Expected Output: Permission denied
  exit
  ```

- **As `dave`:**

  ```bash
  su - dave
  ls /shared    # Should be accessible
  touch /shared/dave_file.txt
  ls -l /shared/dave_file.txt
  exit
  ```

---

### **4. Demonstrate the `setgid` Bit on a Directory**

The `setgid` bit ensures that all new files and subdirectories inherit the group ID of the parent directory (`projA`).

```bash
sudo chmod g+s /shared
ls -ld /shared
# Expected Output: drwxrws---  root projA ...
```

_Explanation:_

- The `s` in the group permissions indicates that the `setgid` bit is set.

**Effect:**

- Any new file or directory created within `/shared` will automatically have `projA` as its group, maintaining consistent group ownership for collaborative work.

#### **Test `setgid` Behavior**

- **As `alice`:**

  ```bash
  su - alice
  touch /shared/alice_new_file.txt
  ls -l /shared/alice_new_file.txt
  # Expected Group: projA
  exit
  ```

- **As `dave`:**

  ```bash
  su - dave
  touch /shared/dave_new_file.txt
  ls -l /shared/dave_new_file.txt
  # Expected Group: projA
  exit
  ```

---

### **5. Demonstrate the `sticky` Bit**

The `sticky` bit is typically set on directories like `/tmp`, allowing users to create files but restricting deletion to file owners, the directory owner, or the root user.

#### **Create a Public Directory with Sticky Bit**

```bash
sudo mkdir /public
sudo chmod 1777 /public
# Permissions: rwxrwxrwt
```

_Explanation:_

- **Sticky Bit (`t`):** Ensures that only the file owner, directory owner, or root can delete or rename files within the directory.
- **Numeric Mode:** `1` (sticky bit) + `777` = `1777`.

#### **Check Permissions**

```bash
ls -ld /public
# Expected Output: drwxrwxrwt
```

#### **Test Sticky Bit Behavior**

- **As `alice`:**

  ```bash
  su - alice
  touch /public/alice_public.txt
  ls -l /public/alice_public.txt
  exit
  ```

- **As `bob`:**

  ```bash
  su - bob
  rm /public/alice_public.txt
  # Expected Output: Permission denied
  exit
  ```

- **As `alice`:**

  ```bash
  su - alice
  rm /public/alice_public.txt
  # Should succeed
  exit
  ```

---

### **6. Demonstrate the `setuid` Bit on an Executable**

The `setuid` bit allows an executable to run with the permissions of the file's owner rather than the user who executes it. **Note:** Applying `setuid` on scripts is generally ineffective and insecure on many systems. It is recommended to use compiled binaries for `setuid` functionality.

#### **Create a File Readable Only by `projA` and Root**

```bash
echo "Secret info for projA only" | sudo tee /shared/secret.txt
sudo chmod 640 /shared/secret.txt
# Permissions: rw for owner (root), r for group (projA), --- for others
```

- **Owner (`root`):** Read, write.
- **Group (`projA`):** Read.
- **Others:** No permissions.

#### **Verify Restricted Access**

- **As `charlie`:**

  ```bash
  su - charlie
  cat /shared/secret.txt
  # Expected Output: Permission denied
  exit
  ```

#### **Create a Setuid Executable**

Since `setuid` on scripts is unreliable, we'll create a simple C program to demonstrate `setuid`.

##### **Create a C Program (`show_secret.c`)**

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Change effective UID to the owner of the file (alice)
    setuid(geteuid());

    FILE *file = fopen("/shared/secret.txt", "r");
    if (file == NULL) {
        perror("Failed to open secret.txt");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Secret: %s\n", buffer);
    } else {
        printf("No secret found.\n");
    }

    fclose(file);
    return 0;
}
```

##### **Compile the Program**

```bash
sudo gcc -o /usr/local/bin/show_secret show_secret.c
sudo chown alice:projA /usr/local/bin/show_secret
sudo chmod 4750 /usr/local/bin/show_secret
# Permissions: rwsr-x--- (setuid bit set)
```

_Explanation:_

- **Setuid Bit (`4` in `4750`):** Ensures the program runs with the privileges of the file owner (`alice`).
- **Permissions:**
  - **Owner (`alice`):** Read, write, execute.
  - **Group (`projA`):** Read, execute.
  - **Others:** No permissions.

##### **Test `setuid` Executable Behavior**

- **As `charlie`:**

  ```bash
  su - charlie
  /usr/local/bin/show_secret
  # Expected Output: "Secret info for projA only"
  exit
  ```

- **As `bob`:**

  ```bash
  su - bob
  /usr/local/bin/show_secret
  # Expected Output: "Secret info for projA only"
  exit
  ```

_Note:_ `charlie` gains access to `secret.txt` through the `setuid` executable, running with `alice`'s privileges.

---

### **7. Changing Permissions Using Numeric and Symbolic Forms**

Demonstrate setting permissions using both numeric (octal) and symbolic modes.

#### **Numeric Mode Examples**

- **Set `/shared` to `rwxrws---` (with `setgid`):**

  ```bash
  sudo chmod 2770 /shared
  ls -ld /shared
  # Expected Output: drwxrws---
  ```

- **Remove Write Permission for Others from `/public`:**

  ```bash
  sudo chmod 1755 /public
  ls -ld /public
  # Expected Output: drwxr-xr-t
  ```

#### **Symbolic Mode Examples**

- **Remove Execute Permission for Group from `/usr/local/bin/show_secret`:**

  ```bash
  sudo chmod g-x /usr/local/bin/show_secret
  ls -l /usr/local/bin/show_secret
  # Expected Output: -rwsr--r-- (execute removed for group)
  ```

- **Add Write Permission for Group on `/shared`:**

  ```bash
  sudo chmod g+w /shared
  ls -ld /shared
  # Expected Output: drwxrws--- (write permission already set for group)
  ```

---

### **8. Demonstrating ACLs and Extended Attributes (Brief)**

**Access Control Lists (ACLs):** Provide more granular permission settings beyond the standard owner-group-others model.

#### **Grant `charlie` Read Access to `/shared/secret.txt` via ACL**

```bash
sudo setfacl -m u:charlie:r /shared/secret.txt
getfacl /shared/secret.txt
```

_Explanation:_

- `setfacl -m u:charlie:r` adds a read permission for `charlie` on `secret.txt`.
- `getfacl` displays the current ACLs, showing `charlie` has read access.

#### **Verify ACLs**

```bash
ls -l /shared/secret.txt
# Expected Output: -rw-r-----+ 1 root projA ...
# The '+' indicates that ACLs are present.
```

#### **View ACLs**

```bash
getfacl /shared/secret.txt
# Example Output:
# # file: /shared/secret.txt
# # owner: root
# # group: projA
# user::rw-
# user:charlie:r--
# group::r--
# mask::r--
# other::---
```

#### **Set Extended Attributes**

Extended attributes store additional metadata for files.

- **View Extended Attributes:**

  ```bash
  getfattr -d /shared/secret.txt
  ```

- **Set an Extended Attribute:**

  ```bash
  sudo setfattr -n user.comment -v "Confidential project file" /shared/secret.txt
  ```

- **Verify Extended Attributes:**

  ```bash
  getfattr -d /shared/secret.txt
  ```

_Note:_ Extended attributes do not appear in the standard `ls -al` output.

---

## **Summary of Demonstrations**

1. **Users and Groups:**

   - Created `projA` and `projB` groups.
   - Assigned users (`alice`, `bob`, `charlie`, `dave`) to these groups with varying primary and supplementary memberships.

2. **Basic Permissions:**

   - Set `/shared` with `rwx` for owner and group, restricting access to `projA` members.
   - Verified access permissions for different users.

3. **Setgid on Directories:**

   - Applied the `setgid` bit on `/shared` to ensure new files inherit the `projA` group.
   - Confirmed consistent group ownership for collaborative files.

4. **Sticky Bit on a Directory (`/public`):**

   - Configured `/public` with `rwxrwxrwt`, allowing all users to create files but restrict deletions to file owners.
   - Demonstrated permission denial for unauthorized deletions.

5. **Setuid on an Executable:**

   - Created a compiled C program `show_secret` with the `setuid` bit, allowing users to access restricted files through elevated privileges.
   - Highlighted the importance of using compiled binaries for `setuid` functionality due to security restrictions on scripts.

6. **Numeric and Symbolic `chmod`:**

   - Showcased both numeric (octal) and symbolic methods for setting and modifying permissions.
   - Applied permissions changes to demonstrate flexibility in permission management.

7. **ACLs and Extended Attributes:**
   - Utilized ACLs to grant specific permissions to users outside of standard group memberships.
   - Demonstrated setting and viewing extended attributes for additional file metadata.
