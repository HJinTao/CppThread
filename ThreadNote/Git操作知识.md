# Git操作知识



## 1.配置SSH key



## 2.关联本地仓库与GitHub上仓库

```sh
git remote add origin git@github.com:HJinTao/CppThread.git #创建一个名为origin的远程仓库
git branch -M main #git init 默认branch名称master而GitHub新repository默认初始branch名称main
git push -u origin main #把本地main分支推送到origin的main分支. -u作用是关联本地main和origin main
```



## 3. .gitignore文件

```sh
#忽略VScode配置文件
.vscode/
#忽略obsidian配置文件
ThreadNote/.obsidian
```

`.gitignore` 只影响**未被 Git 跟踪**的文件。

- #### 若文件未被git跟踪(add)

	.gitignore一更新就马上生效

- #### 若文件已被git跟踪

	1. ##### 取消跟踪一个文件

	```sh
	git rm --cached secret.txt          #--cached 表示在本地文件夹中不删除
	```

	2. ##### 取消跟踪一个文件夹

	```sh
	git rm --cached -r logs/
	```

	

​				