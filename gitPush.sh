#!/bin/bash
read -p "Commit description: " desc
git add . && \
git commit --all -n -m "$desc" && \
git push 