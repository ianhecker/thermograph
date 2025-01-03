# Git

This serves as a tutorial for git on how do basic version control with code

## Install

Install Git https://git-scm.com/

Install text editor Micro https://github.com/zyedidia/micro

## Clone the Repo

To download code into a folder on your local machine:

```bash
git clone https://github.com/ianhecker/thermograph.git thermograph
```

## Repo Permissions for Pushing

You will need to reach out and be added to the repo in order to *push*, but
you'll be able to *pull* and do most of the tutorial without repo permissions

## Code on Main

Main is the name of the root branch on Git. This branch should be treated
specially, and *only be used for merging code that has been approved*

This provides a base source of truth that code editting can stem itself off of

## Pulling Code

To get the latest remote code and branches, you need to pull

```bash
git checkout main
git pull
```

Note, you should avoid editing the `main` branch, as it will cause conflicts
should you try to pull main from the remote, and main has been altered

If you have editted a branch locally, and changes have been made to the branch
remotely, a *merge conflict* will occur when you pull

## Branches

Branches should be created and used for code edits. This allows you to create
a change, and then add another change on top via *commits*.

```bash
git checkout main
git checkout -b my-cool-feature
```

## Committing & Pushing

To save your code changes, you can create commits. Let's create a commit

```bash
git checkout my-cool-feature
touch hello-world.txt
```

Let's check to see the status

```bash
git status
```

The file `hello-world.txt` should be listed as *Untracked*

![git-status-hello-world-file](/images/2024-10-13_18-26-46.png)

Now, let's add the file to git so it can track it

```bash
git add hello-world.txt
```

Let's check to see the status

```bash
git status
```
The file should now listed as *Changes to be committed*

![git-add-hello-world](/images/2024-10-13_18-27-14.png)

Let's add a commit, with a message

```bash
git commit -m "Added hello-world.txt file"
```

Let's check our commits

```bash
git log
```

You can see the list of commits now, and should see yours

![git-log-hello-world](images/2024-10-13_18-28-16.png)

Let's edit the file and add a sentence

```bash
echo "Hello World!" >> hello-world.txt
```

Check the file for the contents, *"Hello World!"*

```bash
micro hello-world.txt
```

Now, check status

```bash
git status
```

The file should be listed in *Changes not staged for commmit*

![git-status-hello-world-edit](images/2024-10-13_18-29-24.png)

Let's run a diff

```bash
git diff
```

Running *diff* will show a file before an edit, and the changes now

![git-diff-hello-world](/images/2024-10-13_18-29-42.png)

Let's add changes

```bash
git add hello-world.txt
```

Now, check status - it should be *Changes to be commited*

```bash
git status
```

![git-status-hello-world-commit](/images/2024-10-13_18-30-01.png)

Let's commit the changes with a message

```bash
git commit -m "Updated hello-world.txt"
```

The file is now committed

Yay! let's push your new branch to the remote repo. You only have to do this
with a new branch that has not yet been *pushed*

```bash
git push -u origin my-cool-feature
```

![git-status-hello-world-commit](/images/2024-10-13_19-02-00.png)

Should you want to add anymore changes to the remote, add more commits and then
*push* your branch

```bash
git push
```

## To Do

1. How to undo of a commit
2. How to reverse unwanted changes back to the previous state
3. How to run git add --patch
4. How to issue Pull Request
5. How to cleanup branches
