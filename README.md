# Train Schedule Management System

A C-based console application for managing train schedules and booking tickets. The system provides separate interfaces for guests and administrators to view schedules, book tickets, and manage train information.

## Features
- User authentication with admin and guest access levels
- Train schedule management (add, delete, modify, search, display)
- Ticket booking system with multiple ticket types
- Booking record management and viewing
- Sales reporting and analytics for administrators
- Booking cancellation for both users and staff
- Persistent data storage using text files

## Installation
```bash
# clone the repo
git clone https://github.com/yourusername/train-schedule-system.git

# navigate to project directory
cd train-schedule-system

# open the solution file in Visual Studio
# TrainScheduleSystem.sln

# build the project using Visual Studio
# Press Ctrl+Shift+B or use Build > Build Solution
```

## Usage

### Running the Application
1. Open `TrainScheduleSystem.sln` in Visual Studio
2. Build and run the project (F5 or Ctrl+F5)
3. Choose login option:
   - Guest: Access train schedules and booking features
   - Admin: Full access to schedule management and booking administration

### Admin Login
Default admin credentials are stored in `users.txt`

### File Structure
- `src/Source.c` - Main source code
- `src/trainschedule.txt` - Train schedule data
- `src/users.txt` - User credentials
- `build/` - Compiled binaries and build artifacts

## Requirements
- Visual Studio 2019 or later
- Windows operating system
- C compiler with C99 support

## Authors
- TAN QI XUAN
- SAMANTHA LAU ZHEN MIAO
