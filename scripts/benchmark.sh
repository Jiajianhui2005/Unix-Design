#!/usr/bin/env bash
set -euo pipefail

ab -n 1000 -c 50 http://127.0.0.1:8080/

