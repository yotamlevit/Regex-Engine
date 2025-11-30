# Enabling Required Status Checks for Pull Requests

To make the CI tests a **required condition** before merging PRs, follow these steps in your GitHub repository:

## Steps to Configure

1. **Go to Repository Settings**

   - Navigate to: `https://github.com/yotamlevit/Regex-Engine/settings`
   - Click on **Branches** in the left sidebar

2. **Add Branch Protection Rule**

   - Click **Add rule** or **Add branch protection rule**
   - Branch name pattern: `main`

3. **Configure Protection Rules**
   Enable these options:

   ✅ **Require a pull request before merging**

   - ✅ Require approvals: `0` or `1` (your choice)

   ✅ **Require status checks to pass before merging**

   - ✅ Require branches to be up to date before merging
   - Search and add these status checks:
     - `test (ubuntu-latest)`
     - `test (macos-latest)`

   ✅ **Do not allow bypassing the above settings** (optional but recommended)

4. **Save Changes**
   - Click **Create** or **Save changes** at the bottom

## What This Does

- ❌ PRs **cannot be merged** if CI tests fail
- ✅ PRs **can only merge** when all tests pass on both Ubuntu and macOS
- 🔒 Protects `main` branch from broken code

## Testing the Configuration

After setup, try creating a PR:

1. The PR page will show "Required checks pending"
2. Once CI completes, it shows "All checks have passed"
3. Merge button becomes available only after all checks pass

## Alternative: GitHub CLI

You can also set this up via GitHub CLI:

```bash
# Enable branch protection with required status checks
gh api repos/yotamlevit/Regex-Engine/branches/main/protection \
  --method PUT \
  --field required_status_checks[strict]=true \
  --field required_status_checks[contexts][]=test \
  --field required_pull_request_reviews[required_approving_review_count]=0 \
  --field enforce_admins=false \
  --field allow_force_pushes=false
```

---

**Note:** This is a repository setting, not a workflow configuration. You'll need admin access to the repository to configure branch protection rules.
