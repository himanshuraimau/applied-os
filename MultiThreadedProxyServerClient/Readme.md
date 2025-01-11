# Multi-Threaded Proxy Server with Caching

A simple HTTP proxy server implementation with caching capabilities and multi-threading support.

## Features

- HTTP GET request handling
- LRU (Least Recently Used) caching mechanism
- Multi-threaded client handling with semaphore-based connection limiting
- Thread-safe cache operations using mutex locks
- Basic error handling with HTTP status codes

## Implementation Details

### Cache Configuration
- Maximum cache size: 200MB (`MAX_SIZE`)
- Maximum single element size: 10MB (`MAX_ELEMENT_SIZE`)
- Maximum concurrent clients: 400 (`MAX_CLIENTS`)

### Main Components

1. **Proxy Server**
   - Listens on specified port (default: 8080)
   - Handles incoming client connections
   - Creates threads for concurrent request handling

2. **Cache System**
   - LRU-based eviction policy
   - Thread-safe operations
   - Stores HTTP responses with their corresponding URLs

3. **Request Handling**
   - Only supports HTTP GET requests
   - Forwards requests to remote servers
   - Returns cached responses when available

## Building and Running

1. **Compile the code:**
   ```bash
   gcc -o proxy_server proxy_server_with_cache.c -lpthread
   ```

2. **Run the server:**
   ```bash
   ./proxy_server <port_number>
   ```
   Example:
   ```bash
   ./proxy_server 8080
   ```

## Limitations

1. Only supports HTTP GET requests
2. No HTTPS support
3. Only handles basic HTTP errors (400, 403, 404, 500, 501, 505)
4. No cache persistence between server restarts

## Error Handling

The server handles the following HTTP error codes:
- 400 Bad Request
- 403 Forbidden
- 404 Not Found
- 500 Internal Server Error
- 501 Not Implemented
- 505 HTTP Version Not Supported

## System Requirements

- POSIX-compliant operating system
- GCC compiler
- pthread library support