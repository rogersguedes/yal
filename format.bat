forfiles /p src /m "*.c" /s /c "cmd /c clang-format --verbose -i @path"
forfiles /p inc /m "*.h" /s /c "cmd /c clang-format --verbose -i @path"
