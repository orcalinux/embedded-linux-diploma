# Hungarian Notation in Modern C++

A comprehensive guide to applying (and understanding) Hungarian-style naming conventions in a modern C++ codebase. Includes recommended prefixes, when to use them, and concrete examples covering raw pointers, smart pointers, containers, member variables, constants, and more.

---

## Table of Contents

- [Hungarian Notation in Modern C++](#hungarian-notation-in-modern-c)
  - [Table of Contents](#table-of-contents)
  - [What Is Hungarian Notation?](#what-is-hungarian-notation)
  - [Why (and Why Not) Use It in Modern C++](#why-and-why-not-use-it-in-modern-c)
  - [General Guidelines](#general-guidelines)
  - [Type Prefixes \& Examples](#type-prefixes--examples)
    - [Boolean](#boolean)
    - [Integral \& Floating](#integral--floating)
    - [Character \& String](#character--string)
    - [Raw Pointers](#raw-pointers)
    - [References](#references)
    - [Smart Pointers](#smart-pointers)
    - [Containers](#containers)
    - [Iterators](#iterators)
  - [Variable Scopes \& Prefixes](#variable-scopes--prefixes)
    - [Member Variables](#member-variables)
    - [Static \& Global Variables](#static--global-variables)
    - [Constant Values](#constant-values)
  - [Function, Class, and Namespace Naming](#function-class-and-namespace-naming)
  - [Putting It All Together: Sample Class](#putting-it-all-together-sample-class)
  - [When to Avoid Hungarian Notation](#when-to-avoid-hungarian-notation)
  - [References \& Further Reading](#references--further-reading)

---

## What Is Hungarian Notation?

Hungarian Notation is a naming convention that prefixes variable names with short identifiers describing either the _type_ (Systems Hungarian) or the _purpose_ (Apps Hungarian). In C++, we typically follow a _lightweight_ Systems Hungarian, where prefixes hint at raw types (e.g. pointers, integers) but don’t encode business logic.

---

## Why (and Why Not) Use It in Modern C++

**Pros:**

- Immediate visual cue of basic type/category
- Helps during rapid prototyping or in deeply template/generic code

**Cons:**

- Redundant when using `auto`, strong typing, or IDE tooltips
- Can clutter names and obscure semantic meaning
- Modern C++ favors expressive names and RAII over manual memory management

Use Hungarian sparingly for raw pointers or legacy interop; prefer semantic names and leverage smart pointers and `auto` where possible.

---

## General Guidelines

- **Stick to lowercase prefixes** (e.g. `b`, `n`, `p`, `up`, `sp`, `v`), then **PascalCase** or **camelCase** for the semantic part.
- **Don’t mix** multiple styles—choose one and apply consistently.
- **Avoid over-prefixing**: if the type is obvious from context (e.g. `auto`, function signature), skip it.
- **Reserve `m_`** for non-static class member variables (`m_nCount`, not `nCount`).

---

## Type Prefixes & Examples

### Boolean

```cpp
bool bIsActive = false;
bool bHasChildren = true;
```

### Integral & Floating

```cpp
int   nCount       = 0;       // n: signed integer
unsigned int unSize = 0u;     // un: unsigned integer
long  lOffset      = 100L;    // l: long
float fRatio       = 0.75f;   // f: float
double dThreshold  = 3.14;    // d: double
```

### Character & String

```cpp
char        cDelimiter     = '\n';
std::string strUserName    = "Alice";
std::wstring wstrFilePath  = L"C:\\path\\file.txt";
```

### Raw Pointers

```cpp
int*      pRawBuffer     = nullptr;
MyClass*  pInstance      = new MyClass();
```

### References

```cpp
int   count = 5;
int&  rCount = count;  // r: reference
```

### Smart Pointers

```cpp
// UP: unique_ptr
std::unique_ptr<Resource> upResource  = std::make_unique<Resource>(args);
// SP: shared_ptr
std::shared_ptr<Widget>   spWidget    = std::make_shared<Widget>(args);
// WP: weak_ptr
std::weak_ptr<Model>      wpModel     = spWidget;
```

### Containers

```cpp
std::vector<int>             vNumbers;     // v: vector
std::list<std::string>       lstNames;     // lst: list
std::map<std::string, int>   mpIndex;      // mp: map
std::unordered_set<int>      usetFlags;    // uset: unordered_set
std::array<double, 4>        arrCoords;    // arr: std::array
```

### Iterators

```cpp
auto itNumber = vNumbers.begin();   // it: iterator
auto citNames = lstNames.cbegin(); // cit: const_iterator
```

---

## Variable Scopes & Prefixes

### Member Variables

- Prefix with `m_`

```cpp
class Foo {
private:
    int   m_nCount       = 0;
    bool  m_bIsEnabled   = false;
    auto  m_upResource   = std::make_unique<Resource>();
};
```

### Static & Global Variables

- Static locals: `s_`
- Globals: `g_`

```cpp
static int  s_nInstanceCount = 0;
int         g_nMaxAllowed    = 100;
```

### Constant Values

- Prefix constants with `k_`

```cpp
constexpr int   k_nMaxConnections = 10;
const std::string k_strAppName    = "MyApp";
```

---

## Function, Class, and Namespace Naming

- **Functions:** use PascalCase or camelCase without Hungarian prefixes

  ```cpp
  void ProcessData(const std::string& strInput);
  int GetNextIndex();
  bool IsValidUser(int nUserID);
  ```

- **Classes/Structs:** PascalCase

  ```cpp
  class  NetworkManager;
  struct Point3D;
  ```

- **Namespaces:** lowercase or company/project style

  ```cpp
  namespace myapp::network {
  // ...
  }
  ```

---

## Putting It All Together: Sample Class

```cpp
#include <string>
#include <vector>
#include <memory>

class Connection {
public:
    Connection(int nID, std::string strHost)
      : m_nConnectionID(nID)
      , m_strHost(std::move(strHost))
    {}

    bool Connect();
    void Disconnect();

private:
    static constexpr int            k_nDefaultPort   = 80;
    int                             m_nConnectionID  = 0;
    std::string                     m_strHost;
    std::unique_ptr<Socket>        m_upSocket;
    std::vector<uint8_t>           m_vReceiveBuffer;
    bool                            m_bIsConnected   = false;
};
```

---

## When to Avoid Hungarian Notation

- In template-heavy or generic code where prefixes add noise
- When modern tooling (IDEs, code completion) already shows types
- For API/public-facing interfaces—favor semantic clarity over type hints

---

## References & Further Reading

- [C++ Core Guidelines: Naming Conventions](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-naming)
- Joel Spolsky, _"The Failure of Hungarian Notation"_, 2002
- Bjarne Stroustrup, _The C++ Programming Language_ (4th Edition)
