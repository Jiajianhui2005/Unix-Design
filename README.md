# HighPerformanceWebServer

## 项目简介

HighPerformanceWebServer 是一个使用 C++17 开发的高性能 Web 服务器课程设计项目。

项目目标是在 Linux / Unix 环境下，从底层 Socket 编程开始，实现一个可运行、可测试、可演示的轻量级 Web 服务器。当前版本已经完成基础工程搭建、配置文件读取和阻塞式 Socket 服务器，后续将继续支持 GET 静态资源、POST 表单、CGI、SQLite 数据库 CRUD、线程池和 epoll 高并发处理。

## 开发环境

- Rocky Linux 9.8
- GCC / G++ 11.5
- CMake 3.31
- GDB 16.3
- SQLite 3
- ApacheBench

当前开发方式：使用 CLion 作为开发 IDE，远程连接 Rocky Linux 环境进行编译、运行和 Debug 调试。

## 项目结构

```text
HighPerformanceWebServer/
├── CMakeLists.txt
├── README.md
├── config/              # 配置文件
├── data/                # 数据库文件目录
├── docs/                # 项目文档
├── include/             # 头文件
├── logs/                # 日志目录
├── scripts/             # 构建、运行和压测脚本
├── src/                 # 源代码
├── tests/               # 测试目录
└── webroot/             # 静态资源目录
```

## 编译方式

```bash
cmake -S . -B build
cmake --build build
```

也可以使用脚本：

```bash
./scripts/build.sh
```

## 运行方式

```bash
./build/webserver config/server.conf
```

也可以使用脚本：

```bash
./scripts/run.sh
```

当前 v0.2 版本预期输出：

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

启动后可以访问：

```bash
curl http://127.0.0.1:8080/
```

或在浏览器中打开：

```text
http://127.0.0.1:8080/
```

## 配置文件

默认配置文件路径：

```text
config/server.conf
```

配置示例：

```text
port=8080
thread_num=4
webroot=./webroot
database=./data/server.db
log_file=./logs/server.log
```

当前支持的配置项：

| 配置项 | 说明 |
|---|---|
| `port` | 服务器监听端口 |
| `thread_num` | 线程池线程数量，当前为后续线程池功能预留 |
| `webroot` | 静态资源目录 |
| `database` | SQLite 数据库文件路径 |
| `log_file` | 日志文件路径 |

## 当前已实现功能

- CMake 工程骨架。
- C++17 编译配置。
- 配置文件读取。
- TCP Socket 创建、绑定和监听。
- 阻塞式 `accept` 接收客户端连接。
- 使用 `recv` 读取 HTTP 请求。
- 返回基础 `HTTP/1.1 200 OK` HTML 响应。
- 使用 `sendAll` 保证响应内容完整发送。
- 已准备 `webroot` 静态资源目录。
- 已准备构建、运行和压测脚本。

## 开发路线

1. v0.1：完成 CMake 项目骨架。
2. v0.2：完成阻塞式 Socket 服务器，返回固定 HTML。
3. v0.3：支持 GET 静态文件服务器和 404 页面。
4. v0.4：支持 POST 表单解析。
5. v0.5：支持 CGI。
6. v0.6：支持 SQLite CRUD 页面。
7. v0.7：实现线程池。
8. v0.8：实现 epoll 非阻塞 IO。
9. v1.0：完成压测报告和课程设计交付。

## 压测

后续功能稳定后，可以使用 ApacheBench 进行基础压测：

```bash
./scripts/benchmark.sh
```

脚本当前命令：

```bash
ab -n 1000 -c 50 http://127.0.0.1:8080/
```

## 文档

项目文档位于 `docs/` 目录，当前包括：

- `开发计划.md`
- `功能列表清单.md`
- `软件设计规格说明书.md`
- `项目开始答辩材料.md`
