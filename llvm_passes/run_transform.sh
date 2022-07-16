LLVM_INSTALL_DIR=~/projects/llvm-project/build

LLVM_OPT=$LLVM_INSTALL_DIR/bin/opt

$LLVM_OPT -load-pass-plugin build/lib/libAddConst.so \
  -passes="add-const" -S examples/foo.ll \ # S代表输出为文本
  -o examples/foo2.ll

