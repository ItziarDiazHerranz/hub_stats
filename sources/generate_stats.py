import os
import requests

def get_total_commits(username):
    token = os.getenv("GH_TOKEN")
    if not token:
        print("❌ GH_TOKEN environment variable not set")
        return 0

    headers = {
        "Authorization": f"token {token}",
        "User-Agent": "github-stats-script"
    }

    url = f"https://api.github.com/users/{username}/repos"
    total_commits = 0

    response = requests.get(url, headers=headers)
    if response.status_code != 200:
        print(f"❌ Failed to fetch repos for user {username}")
        return 0

    repos = response.json()

    for repo in repos:
        commits_url = repo.get("commits_url", "").replace("{/sha}", "")
        if not commits_url:
            continue

        commits_resp = requests.get(commits_url, headers=headers)
        if commits_resp.status_code != 200:
            continue

        commits = commits_resp.json()
        total_commits += len(commits)

    return total_commits

def get_grade(commits):
    if commits <= 200:
        return "D"
    elif commits <= 400:
        return "D+"
    elif commits <= 600:
        return "C"
    elif commits <= 800:
        return "C+"
    elif commits <= 1000:
        return "B"
    elif commits <= 2000:
        return "B+"
    elif commits <= 4000:
        return "A"
    else:
        return "A+"

def main():
    username = "ItziarDiazHerranz"
    commits = get_total_commits(username)
    grade = get_grade(commits)

    with open("STATS.md", "w") as f:
        f.write(f"## GitHub Stats for {username}\n")
        f.write(f"Total Commits: {commits}\n")
        f.write(f"Commit Grade: {grade}\n")

if __name__ == "__main__":
    main()
