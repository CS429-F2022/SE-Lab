#!/bin/bash

git remote add ref git@github.com:CS429-F2022/SE-Lab.git
git config pull.rebase false
git pull --allow-unrelated-histories --set-upstream ref main --no-commit -X theirs
git commit -m "pulled checkpoint"
git push -u origin main