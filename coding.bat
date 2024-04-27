@echo off
if not exist %1 (
	mkdir %1
)
code %1