# CMakeList.txt : thug-lang の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (thug-lang "thug-lang.cpp" "thug-lang.h"  "src/tokenizer/chunks.cpp" "src/tokenizer/chunks.h" "src/tokenizer/tokenizer.cpp" "src/tokenizer/tokenizer.h" "src/utils/string_util.cpp" "src/utils/string_util.h" "src/test/test.cpp" "src/test/test.h"  "src/Types/types.h" "src/parser/parser.cpp" "src/parser/parser.h")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET thug-lang PROPERTY CXX_STANDARD 20)
endif()

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。
