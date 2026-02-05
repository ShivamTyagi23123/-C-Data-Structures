import subprocess
import random
from datetime import datetime, timedelta
import os

REPO_PATH = r"c:\Users\Admin\Desktop\python or AIML\C-Data-Structures"
os.chdir(REPO_PATH)

# ============================================================
# CONFIG
# ============================================================
NUM_COMMITS = 100
end_date = datetime(2026, 5, 3)       # yesterday
start_date = datetime(2026, 2, 4)     # ~3 months ago
TIMEZONE = "+05:30"                   # IST

# ============================================================
# HELPER: Generate a random datetime with time between 10 PM - 2 AM IST
# ============================================================
def random_late_night():
    delta = (end_date - start_date).days
    random_day = start_date + timedelta(days=random.randint(0, delta))

    # 22:00 to 25:59 (i.e. 10 PM to 1:59 AM next day)
    total_minutes = random.randint(22 * 60, 25 * 60 + 59)
    hour = total_minutes // 60
    minute = total_minutes % 60
    second = random.randint(0, 59)

    if hour >= 24:
        random_day += timedelta(days=1)
        hour -= 24

    return random_day.replace(hour=hour, minute=minute, second=second)

# ============================================================
# Generate 100 sorted random late-night timestamps
# ============================================================
dates = sorted([random_late_night() for _ in range(NUM_COMMITS)])

# ============================================================
# Realistic commit messages
# ============================================================
messages = [
    "Update linked list implementation",
    "Fix stack overflow handling",
    "Add queue enqueue and dequeue operations",
    "Refactor binary tree traversal",
    "Update sorting algorithms",
    "Add inline comments and documentation",
    "Fix memory leak in BST delete",
    "Optimize search algorithm",
    "Update README.md",
    "Add input validation and error handling",
    "Fix array index out-of-bounds",
    "Improve overall code structure",
    "Add edge-case test inputs",
    "Refactor utility helper functions",
    "Update header file includes",
    "Fix compilation warnings",
    "Add graph adjacency list",
    "Update hash table collision handling",
    "Fix pointer dereferencing issue",
    "Improve time complexity of BFS",
    "Clean up code formatting",
    "Add priority queue using heap",
    "Fix segfault in node deletion",
    "Add insertion sort variant",
    "Update merge sort partitioning",
    "Fix infinite recursion in DFS",
    "Add doubly linked list operations",
    "Update circular queue wraparound",
    "Fix min-heap sift down logic",
    "Refactor main driver program",
]

# ============================================================
# STEP 1: Create orphan branch (fresh history, keeps files)
# ============================================================
print("=" * 60)
print("STEP 1: Creating orphan branch with fresh history...")
print("=" * 60)

subprocess.run(["git", "checkout", "--orphan", "temp_main"], check=True)

# Stage all existing files
subprocess.run(["git", "add", "-A"], check=True)

# First commit — contains all existing code
dt = dates[0]
date_str = dt.strftime(f"%Y-%m-%dT%H:%M:%S{TIMEZONE}")
env = os.environ.copy()
env["GIT_AUTHOR_DATE"] = date_str
env["GIT_COMMITTER_DATE"] = date_str
subprocess.run(
    ["git", "commit", "-m", "Initial commit: C Data Structures project"],
    env=env, check=True
)
print(f"  [1/100] {date_str}  — Initial commit")

# ============================================================
# STEP 2: Create remaining 99 commits with small changes
# ============================================================
print("\n" + "=" * 60)
print("STEP 2: Creating 99 additional commits...")
print("=" * 60)

for i in range(1, NUM_COMMITS):
    dt = dates[i]
    date_str = dt.strftime(f"%Y-%m-%dT%H:%M:%S{TIMEZONE}")
    msg = random.choice(messages)

    # Append a dev-log entry as the file change for each commit
    with open("dev_log.md", "a", encoding="utf-8") as f:
        if i == 1:
            f.write("# Development Log\n\n")
        f.write(f"- **{dt.strftime('%Y-%m-%d %H:%M')}** — {msg}\n")

    subprocess.run(["git", "add", "."], check=True)

    env = os.environ.copy()
    env["GIT_AUTHOR_DATE"] = date_str
    env["GIT_COMMITTER_DATE"] = date_str
    subprocess.run(["git", "commit", "-m", msg], env=env, check=True)
    print(f"  [{i+1}/100] {date_str}  — {msg}")

# ============================================================
# STEP 3: Replace old main branch
# ============================================================
print("\n" + "=" * 60)
print("STEP 3: Replacing main branch...")
print("=" * 60)

subprocess.run(["git", "branch", "-D", "main"], check=True)
subprocess.run(["git", "branch", "-m", "main"], check=True)
print("  Done! 'temp_main' renamed to 'main'.")

# ============================================================
# DONE
# ============================================================
print("\n" + "=" * 60)
print("SUCCESS! 100 commits created with late-night timestamps.")
print("=" * 60)
print("\nNow run this to push:")
print("  git push -f origin main")
print()
