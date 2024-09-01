# Multi-Level Page Table Simulator
This project implements a simulated OS code that handles a multi-level (trie-based) page table for a 64-bit x86-like CPU

# Implements a 5-level page table structure
Supports 57-bit virtual addresses
Provides functions for creating, destroying, and querying virtual memory mappings
Simulates OS functionality for physical memory management

# Implementation Details
The main components of this project are:

page_table_update: Creates or destroys virtual memory mappings in the page table
page_table_query: Queries the mapping of a virtual page number in the page table

The page table structure uses 4 KB pages and 64-bit page table entries.
Building and Running

# File Structure

pt.c: Contains the implementation of the page table functions
os.h: Header file with function prototypes and constants
os.c: Simulates OS functionality and contains the main function with basic tests
