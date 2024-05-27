@echo off
cd /d d:\code
if not exist %1 ( mkdir %1 )
code %1