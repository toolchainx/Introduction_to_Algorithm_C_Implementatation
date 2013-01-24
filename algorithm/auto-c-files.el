;; 编写一个自动创建C语言源文件和头文件的程序
;; 创建的文件是为了进行算法导论中算法实现的练习
;; 创建的文件有
;; filename.c 内容包含#include "filename.h"
;; filename_test.c 内容包含#include "filename.h"　及 main
;; filename.h 内容包含once 预处理
;; filename.mk 内容包含makefile的模板，在algorithm/make_template.mk中
;; 程序的输入为 filename

;; 检测名为filename.*的文件是否存在，(*代表任意的扩展名)
(defun auto-c-files (filename template-filename)
  "auto generate files named \"filename\" for C development"
  (interactive "sEnter the file name sans extension: \nsEnter the template file name: ")
  (message "File name: %s, template file name: %s" filename template-filename)
  (if (directory-files "." nil 
		       (concat
			filename "\..*")
		       t)
      (message "%s already exists!" filename)
    (if (file-exists-p template-filename)
	(progn
	  (dot-c-file filename)
	  (dot-c-test-file filename)
	  (dot-h-file filename))
      (message "can't find the template file in current dir."))))
(defun dot-c-file (filename)
  (let ((filename-ext (concat filename ".c")))
    (if (not (file-exists-p filename-ext))
	(write-region 
	 (concat "#include \"" filename ".h\"\n") 
	 nil 
	 filename-ext
	 t)
    (message (concat 
		filename-ext
		" already exist!")))))
;; 包含once预处理  
(defun dot-h-file (filename)
  (let ((filename-ext (concat filename ".h"))
	(filename-ext-h-tag 
	 (concat 
	  "_"
	  (upcase (file-name-nondirectory 
		   (file-name-sans-extension filename))) 
	  "_H_")))
    (if (not (file-exists-p filename-ext))
	  (write-region
	   (concat 
	    "#ifndef " filename-ext-h-tag "\n"
	    "#define " filename-ext-h-tag "\n\n\n"
	    "#endif /* " filename-ext-h-tag " */"
	    )
	   nil 
	   filename-ext
	   t)	
      (message (concat 
		filename-ext
		" already exist!")))))
;; 填充头文件及main模板
(defun dot-c-test-file (filename)
  (let ((filename-ext (concat filename "_test.c")))
    (if (not (file-exists-p filename-ext))
	  (write-region 
	   (concat 
	    "#include \"" filename ".h\"\n\n"
	    "int main(int argc, char *argv[])\n"
	    "{\n\n\n"
	    "    return 0;\n"
	    "}")  
	   nil 
	   filename-ext
	   t)
      (message (concat 
		filename-ext
		" already exist!")))))
;; 填充makefile模板
;; copy-file
(defun dot-make-file (filename template-filename)
  (let ((filename-ext (concat filename ".mk")))
    (if (not (file-exists-p filename-ext))
	(if (file-exists-p template-filename)
	    (copy-file template-filename filename-ext)
	  (message "template file is not exist!"))
      (message (concat 
		filename-ext
		" already exist!")))))

(provide 'auto-c-files)
