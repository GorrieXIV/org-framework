OrgEngine - the Origins Realtime Game Engine
============================================
[![Build Status](https://travis-ci.com/GorrieXIV/OrgEngine.svg?token=snBiXmcUC8gfN5NqbuxD&branch=master)](https://travis-ci.com/GorrieXIV/OrgEngine)

## Installing Dependencies

1. Execute `sudo bin/install_deps.sh` on linux-based systems, or simply `./bin/install_deps.sh` on MacOS, to install the project dependencies.

## Instructions for Contributing

### Setting Up

1. Fork this repository by using the button on the top-right of the repo's github page.
2. Clone your fork locally: `git clone https://github.com/<your_github_account>/OrgEngine.git`
3. Move into the repo: `cd <path_to_repository>`
2. Add the upstream repo as a remote: `git remote add upstream https://github.com/GorrieXIV/OrgEngine.git`
3. Append some useful git helpers to your gitconfig: `cat etc/gitconfig >> ~/.gitconfig`

### Adding Code
Whenever adding functionality or fixing bugs, following this procedure can help reduce risk and keep things organized:
1. `git upmaster`
2. Create a new branch for your addition, with a suitable name: `git checkout -b <suitable_branch_name>`
3. Add your feature/bugfix
4. Push your branch online (this step can be done at any point in your development, after the branch is created): `git push -u origin <suitable_branch_name>`
5. Once the addition is ready to be added, create a pull request for the branch:
    * Select the "Pull requests" tab on the repo's Github page
    * Click the green "New pull request" button on the right-side of the page
    * Click the blue "compare across forks" link to create a PR from your fork
    * Add a useful PR title and description

## Libraries
* **libplatform**
* **libmath**
* **libtime**
* **libphysics**
* **libentities**
* **libdisplay**
* **libcontroller**

## Contributors
* Robert Gorrie
* Serge Cosman Agraz
