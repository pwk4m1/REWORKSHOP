#!/bin/bash
set -e
echo 0 << /proc/sys/kernel/yama/ptrace_scope

