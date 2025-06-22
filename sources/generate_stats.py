import requests

def get_total_commits(username):
    url = f"https://api.github.com/users/{username}/repos"
    response = requests.get(url, headers={"User-Agent": "Custom"})
    repos = response.json()
    total_commits = 0
    for repo in repos:
        commits_url = repo["commits_url"].replace("{/sha}", "")
        commits_resp = requests.get(commits_url)
        if commits_resp.status_code == 200:
            total_commits += len(commits_resp.json())  # solo los primeros por limitación
    return total_commits

def get_grade(commits):
    if commits <= 200: return "D"
    elif commits <= 400: return "D+"
    elif commits <= 600: return "C"
    elif commits <= 800: return "C+"
    elif commits <= 1000: return "B"
    elif commits <= 2000: return "B+"
    elif commits <= 4000: return "A"
    else: return "A+"

commits = get_total_commits("ItziarDiazHerranz")
grade = get_grade(commits)

with open("STATS.md", "w") as f:
    f.write(f"## GitHub Stats for ItziarDiazHerranz\n")
    f.write(f"Total Commits: {commits}\n")
    f.write(f"Commit Grade: {grade}\n")
