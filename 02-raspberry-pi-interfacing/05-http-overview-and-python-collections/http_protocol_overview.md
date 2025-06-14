# HTTP Protocol – Overview and Basics

The Hypertext Transfer Protocol (HTTP) is the foundation of data communication on the web. It follows a **request-response** model where a **client** (e.g., a web browser) sends a request, and a **server** (e.g., a web server) sends back a response.

This document covers the **protocol style**, the **request and response** formats, **HTTP methods**, and **common status codes** with brief explanations.

---

## Table of Contents

- [HTTP Protocol – Overview and Basics](#http-protocol--overview-and-basics)
  - [Table of Contents](#table-of-contents)
  - [What is HTTP?](#what-is-http)
  - [HTTP Message Structure](#http-message-structure)
    - [1. HTTP Request](#1-http-request)
    - [2. HTTP Response](#2-http-response)
  - [HTTP Methods](#http-methods)
  - [HTTP Response](#http-response)
  - [HTTP Status Codes](#http-status-codes)
  - [Conclusion](#conclusion)

---

## What is HTTP?

- **Hypertext Transfer Protocol (HTTP)** is an **application-level** protocol for distributed, collaborative, hypermedia information systems.
- It follows a **client-server** model: a client sends a request, and the server processes that request and returns a response.
- HTTP is typically used over **TCP/IP**, with port **80** as the default for unencrypted communication and port **443** for encrypted HTTPS.

---

## HTTP Message Structure

HTTP communication involves two main message types:

1. **Request** – Sent by the client.
2. **Response** – Sent by the server.

### 1. HTTP Request

An HTTP request generally includes:

```
METHOD /path/resource HTTP/version
Header-Name: Header-Value
Header-Name: Header-Value

[Optional Body]
```

- **Start Line**: Contains the HTTP method (e.g., `GET`, `POST`), the target resource path (e.g., `/hello`), and the protocol version (e.g., `HTTP/1.1`).
- **Headers**: Provide metadata such as `Host`, `User-Agent`, `Content-Type`, etc.
- **Body** (optional): Contains data sent by the client (e.g., form data, JSON, etc.), used primarily with methods like `POST` or `PUT`.

### 2. HTTP Response

An HTTP response generally includes:

```
HTTP/version status_code status_text
Header-Name: Header-Value
Header-Name: Header-Value

[Optional Body]
```

- **Status Line**: Contains the HTTP version (e.g., `HTTP/1.1`), the status code (e.g., `200`), and a brief status text (e.g., `OK`).
- **Headers**: Provide response metadata such as `Content-Type`, `Content-Length`, etc.
- **Body** (optional): Contains the data returned by the server (e.g., HTML, JSON, images, etc.).

---

## HTTP Methods

HTTP methods (sometimes called **verbs**) define the intended action on a given resource:

1. **GET**

   - Retrieves data from the server.
   - The request body is usually empty.
   - Safe and idempotent (should not change server state).

2. **POST**

   - Sends data to the server to create or update a resource.
   - Commonly used with HTML forms or APIs that accept JSON.
   - Not idempotent (each request could create a new resource).

3. **PUT**

   - Replaces all current representations of the target resource with the uploaded content.
   - Idempotent (repeated calls produce the same result).

4. **PATCH**

   - Partially modifies an existing resource.
   - Not necessarily idempotent, but can be designed to be so.

5. **DELETE**

   - Removes the specified resource.
   - Idempotent (once deleted, repeating the call should not produce a new effect).

6. **HEAD**

   - Similar to GET, but returns only the headers (no body).
   - Used to check resource availability or metadata.

7. **OPTIONS**

   - Returns the HTTP methods supported by the server for a specific URL or resource.

8. **TRACE**
   - Echoes back the request for debugging purposes.

---

## HTTP Response

After the server processes the request, it returns an HTTP response consisting of:

1. **Status Line**

   - Contains the HTTP version, status code, and status text.

2. **Headers**

   - Provide details like `Content-Type`, `Content-Length`, `Cache-Control`, etc.

3. **Body** (optional)
   - Contains the requested data (e.g., HTML for a web page, JSON for an API response).

---

## HTTP Status Codes

HTTP status codes are grouped by their first digit:

- **1xx: Informational**
  - **100 Continue** – Indicates that the initial part of a request has been received and has not yet been rejected by the server.
- **2xx: Success**

  - **200 OK** – Request succeeded; the response contains the requested data.
  - **201 Created** – Request succeeded; a new resource was created.

- **3xx: Redirection**

  - **301 Moved Permanently** – The resource has moved to a new permanent URL.
  - **302 Found** (or **302 Moved Temporarily**) – The resource is temporarily at a different URL.
  - **304 Not Modified** – Cached resource has not changed; no new data is returned.

- **4xx: Client Error**

  - **400 Bad Request** – The request was malformed or invalid.
  - **401 Unauthorized** – Authentication is required or failed.
  - **403 Forbidden** – The server understood the request, but refuses to authorize it.
  - **404 Not Found** – The requested resource could not be found.
  - **405 Method Not Allowed** – The method is not supported for the requested resource.

- **5xx: Server Error**
  - **500 Internal Server Error** – A generic error message for an unexpected condition.
  - **502 Bad Gateway** – Invalid response from an upstream server.
  - **503 Service Unavailable** – The server is currently unable to handle the request (overload or down for maintenance).
  - **504 Gateway Timeout** – The server did not receive a timely response from an upstream server.

---

## Conclusion

HTTP is a **stateless**, **request-response** protocol that defines how clients and servers communicate over the web. Understanding the **structure of requests and responses**, the **available methods**, and the **meaning of common status codes** is essential for building and troubleshooting web applications.

**Key Points**:

- HTTP is stateless by default, meaning each request is independent.
- Methods (verbs) indicate the intended action (GET, POST, PUT, etc.).
- Status codes help clients interpret the outcome of their requests.

For more advanced topics, you can explore **HTTP/2**, **HTTP/3**, **TLS/SSL**, **caching mechanisms**, and **RESTful** or **GraphQL** APIs.
