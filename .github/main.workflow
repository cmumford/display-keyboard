workflow "PR Audit" {
  on = "pull_request"
  resolves = ["EC Audit PR"]
}

action "EC Audit PR" {
  uses = "zbeekman/EditorConfig-Action@master"
  # secrets = ["GITHUB_TOKEN"] # Will be needed for fixing errors
  env = {
    EC_FIX_ERRORS = "false" # not yet implemented
    ALWAYS_LINT_ALL_FILES = "true" # Only check files in PR.
  }
}

workflow "Push Audit" {
  on = "push"
  resolves = ["EC Audit Push"]
}

action "EC Audit Push" {
  uses = "zbeekman/EditorConfig-Action@master"
  # secrets = ["GITHUB_TOKEN"] # Will be needed for fixing errors
  env = {
    EC_FIX_ERROR = "false" # not yet implemented
    ALWAYS_LINT_ALL_FILES = "true" # Might be slow for large repos
  }
}

