# AI-Powered C Testing Workflows

This repository contains GitHub Actions workflows that enable AI-powered test generation and execution for C projects. These workflows can be easily integrated into any C repository to automate testing workflows.

## 🚀 Quick Setup

### 1. Add Workflows to Your Repository

Copy the following workflow files to your C repository's `.github/workflows/` directory:

- [`ai-test-generation.yml`](.github/workflows/ai-test-generation.yml) - Generates AI tests
- [`ai-test-execution.yml`](.github/workflows/ai-test-execution.yml) - Runs AI tests

### 2. Set Up Required Secrets

In your repository settings, add the following secret:

- `GOOGLE_API_KEY`: Your Google AI API key for test generation

### 3. Repository Structure Requirements

Your C repository should have:
```
your-c-repo/
├── src/           # Source files (.c, .h)
├── tests/         # Test files (will be created/updated by AI)
└── .github/
    └── workflows/
        ├── ai-test-generation.yml
        └── ai-test-execution.yml
```

## 🎯 Usage

### Generate Tests

1. Create a new issue in your repository
2. Add the label `ai-test-gen` to the issue
3. The workflow will automatically:
   - Analyze your source code in the `src/` directory
   - Generate comprehensive unit tests using AI
   - Commit the tests back to your repository
   - Comment on the issue with completion status

### Run Tests

1. Create a new issue in your repository
2. Add the label `ai-test-run` to the issue
3. The workflow will automatically:
   - Compile and run all tests
   - Generate detailed test reports
   - Comment on the issue with test results
   - Upload test reports as artifacts

## 📋 Workflow Details

### AI Test Generation (`ai-test-gen` label)

**Triggers**: Issue created or labeled with `ai-test-gen`

**Actions**:
- Checks out your repository and the AI tools
- Generates unit tests for all C functions found in `src/`
- Automatically adds Unity testing framework integration
- Commits generated tests with descriptive commit message
- Comments on the issue with results

**Generated Files**:
- `tests/test_*.c` - Individual test files for each source file
- Unity framework integration with proper main functions

### AI Test Execution (`ai-test-run` label)

**Triggers**: Issue created or labeled with `ai-test-run`

**Actions**:
- Checks out your repository and AI tools
- Installs build dependencies (CMake, build tools, lcov)
- Compiles and runs all tests
- Generates individual test reports in `tests/test_reports/`
- Comments on the issue with pass/fail summary
- Uploads detailed test reports as workflow artifacts

**Test Reports**:
- Individual reports for each test executable
- Detailed execution output and error messages
- Test counts (passed/failed) for each executable

## 🔧 Requirements

### System Dependencies (automatically installed)
- CMake
- build-essential (GCC, Make)
- lcov (for coverage reporting)

### Python Dependencies (automatically installed)
- AI Test Generator requirements
- AI Test Runner package

### Source Code Requirements
- C source files in `src/` directory
- Standard C syntax (compatible with GCC)
- Functions that can be unit tested

## 📊 Test Reports

When tests are executed, detailed reports are generated in `tests/test_reports/`:

```
tests/test_reports/
├── test_module1.exe_report.txt
├── test_module2.exe_report.txt
└── ...
```

Each report contains:
- Execution summary (pass/fail, exit code)
- Individual test counts
- Complete Unity test output
- Error details for failed tests

## 🛠️ Troubleshooting

### Tests Not Generated
- Ensure `src/` directory contains `.c` and `.h` files
- Check that `GOOGLE_API_KEY` secret is set correctly
- Verify source files have testable functions

### Tests Fail to Compile
- Check for missing dependencies in source code
- Ensure header files are properly included
- Verify Unity framework download (temporary network issues)

### Workflow Doesn't Trigger
- Ensure issue has the exact label: `ai-test-gen` or `ai-test-run`
- Check repository settings for workflow permissions
- Verify workflows are in `.github/workflows/` directory

## 🤝 Contributing

These workflows use the following AI tools:
- **AI C Test Generator**: `SwathantraPulicherla/ai-c-test-generator`
- **AI Test Runner**: `SwathantraPulicherla/ai-test-runner`

Issues and improvements should be reported in the respective tool repositories.

## 📄 License

These workflows are provided as-is for automating C project testing. The underlying AI tools have their own licenses.