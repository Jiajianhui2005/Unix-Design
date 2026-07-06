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

Expected v0.2 output:

```text
Config file: config/server.conf
Thread count: 4
Web root: ./webroot
Database: ./data/server.db
Log file: ./logs/server.log
HighPerformanceWebServer v0.2.0
Listen port: 8080
Blocking socket server is running.
Open http://127.0.0.1:8080/ in your browser.
```

Then visit:

```bash
curl http://127.0.0.1:8080/
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
