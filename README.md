# HighPerformanceWebServer

C++ high-performance web server course project.

## Environment

- Rocky Linux 9.8
- GCC/G++ 11.5
- CMake 3.31
- GDB 16.3
- SQLite 3
- ApacheBench

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/webserver config/server.conf
```

Expected v0.1 output:

```text
HighPerformanceWebServer v0.1.0
Config file: config/server.conf
Listen port: 8080
Thread count: 4
Web root: ./webroot
Database: ./data/server.db
Log file: ./logs/server.log
Project skeleton is ready.
```

## Roadmap

1. v0.1: CMake project skeleton.
2. v0.2: Blocking socket server returning fixed HTML.
3. v0.3: GET static file server and 404 page.
4. v0.4: POST form parsing.
5. v0.5: CGI support.
6. v0.6: SQLite CRUD pages.
7. v0.7: Thread pool.
8. v0.8: epoll non-blocking IO.
9. v1.0: Benchmark report and course delivery.

