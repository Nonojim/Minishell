### **BIBLIOGRAPHIE** 
---
 - **Concepts et théorie des shells**

    - Chapitre 5 – Writing Your Own Shell (Purdue)
    https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

    - POSIX Shell Command Language (OpenGroup)
    https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html

    - Backus–Naur Form (Wikipedia)
    https://en.wikipedia.org/wiki/Backus–Naur_form

    - Abstract Syntax Tree (Wikipedia)
    https://en.wikipedia.org/wiki/Abstract_syntax_tree

 
- **Lexers et analyseurs**

    - GeeksForGeeks – C Lexical Analyzer
    https://www.geeksforgeeks.org/c-lexical-analyser-lexer/

    - Lexer d’un projet universitaire (en language COOL)
    https://theory.stanford.edu/~aiken/software/cooldist/src/PA3/tokens-lex.cc

    - Shell Grammar Parser
    https://shell.multun.net/parser.html#lire-une-grammaire

 - **Projets GitHub utiles**

    - Swoorup/mysh
    https://github.com/Swoorup/mysh

    - pmouhali/minishell_ast
    https://github.com/pmouhali/minishell_ast

    - vietdu91/42_minishell
    https://github.com/vietdu91/42_minishell

- **Vidéos**

    - How to Build a Shell – YouTube (style 42)
    https://www.youtube.com/watch?v=ubt-UjcQUYg

    - Shell parsing & tokenization – YouTube
    https://www.youtube.com/watch?v=ZjzMdsTWF0U

- **Gros manuels, livres et docu**

    - Manuel officiel de Bash (GNU)
    https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html

    - Man bash en français
    http://manpagesfr.free.fr/man/man1/bash.1.html

    - Advanced Bash Scripting Guide – Chapitre 20 (fr)
    https://abs.traduc.org/abs-5.3-fr/ch20.html#:~:text=D%C3%A9finition%20%3A%20un%20sous-shell%20est,ou%20dans%20une%20fen%C3%AAtre%20xterm

    -    Crafting Interpreters 
    https://craftinginterpreters.com/

    - Learning the Bash Shell (O'Reilly)
    https://github.com/Ricky-Wilson/Programming-books/blob/master/PDF/Learning%20the%20bash%20Shell%2C%203rd%20Edition.pdf

- **Outils pratiques, schemas**

    - Apprendre le Git Branching (visual tool)
    https://learngitbranching.js.org/

    - 800 test
    https://docs.google.com/spreadsheets/d/1BPW7k81LJPhGv2fbi35NIIoOC_mGZXQQJDnV0SjulFs/edit?pli=1&gid=0#gid=0

    - Schema AST
    https://github.com/user-attachments/assets/ff4c3a10-950b-4805-85f9-0088f4edfb43

## Commmandes qui doivent être exe dans Minishell
---
| Nom de la commande | Prototype / Utilisation | Description |
|:-------------------|:------------------------|:------------|
| echo | `echo [OPTIONS] [texte]` | Affiche le txt passé en arg avec ou sans \n [-n] |
| cd | `cd [répertoire]` | Modifie emplacement |
| pwd | `pwd` | Affiche le chemin absolu du répertoire actuel |
| export | `export VAR=valeur` | Définir une variable d'environnement |
| unset | `unset VAR` | Supprime une variable d'environnement |
| env | `env` | Affiche l'environnement actuel |
| exit | `exit` | Termine le script |


## Opérateurs du shell Bash
---
### **Opérateurs logiques**

| Opérateur | Nom              | Effet |
|-----------|------------------|-------|
| `;`       | Séquence         | Exécute les commandes l’une après l’autre, peu importe si la précédente réussit ou échoue. |
| `&&`      | ET logique       | Exécute la commande suivante seulement si la commande précédente réussit. |
| `||`      | OU logique       | Exécute la commande suivante seulement si la commande précédente échoue  |
| `&`       | Tâche en arrière-plan | Lance une commande en arrière-plan, il est alos possible de continuer a utiliser le terminal, permet de faire plusieurs taches en même temps sans qu'elle se bloquent |

### **Pipes**
| Opérateur | Nom              | Effet |
|-----------|------------------|-------|
| `\|`       | Pipe        |  Envoie la sortie standard d’une commande comme entrée de la suivante |

### **Opérateurs de redirection**

| Opérateur | Nom              | Fonction |
|-----------|------------------|----------|
| `<`       | Redirection d’entrée       | Prend l’entrée standard depuis un fichier. |
| `>`       | Redirection de sortie      | Écrit la sortie standard dans un fichier. |
| `>>`      | Redirection de sortie (append) | Ajoute la sortie d une commande à la fin du fichier. |
| `<<`      | **Heredoc** (Here-document) | Lis une entrée multi-lignes jusqu’à un délimiteur (souvent utilisé pour des scripts inline). |

### **Autres opérateurs**

| Opérateur | Nom               | Fonction |
|-----------|-------------------|----------|
| `'`       | simple quote | entoure une chaîne de caractères, les variables ne sont pas interprétées à l'intérieur. ex : `'Hello $USER'` |
| `"`       | double quote | entoure une chaîne où les variables seront interprétées. Ex : USER = toi "`Hello $USER`" devient `Hello toi`|
| `()`      | Subshell          | exe une commande dans un **sous_shell**, permet de ne pas modifier le shell principal |

---

  ### **Fonctions externes autorisées:**

---

- Ok Libft
- printf, malloc, free, write, open, read, close, exit, strerror, perror,

| Nom de la fonction | Prototype | Description |
|:-------------------|:----------|:------------|
| readline | `char *readline(const char *prompt);` | Lit une ligne complète entrée par l'useur, retourne une chaîne allouée dynamiquement sans \n. Présente des leaks ! |
| rl_clear_history | `void rl_clear_history(void);` | Efface l'historique des lignes lues pendant l'exécution. |
| rl_on_new_line | `int rl_on_new_line(void);` |   |
| rl_replace_line | `int rl_replace_line(const char *text, int clear_undo);` |  |
| rl_redisplay | `void rl_redisplay(void);` |  |
| add_history | `void add_history(const char *line);` | Ajoute une ligne à l'historique |
| access | `int access(const char *pathname, int mode);` | Vérif l'existence et l'accessibilité d'un fichier ou dossier |
| fork | `pid_t fork(void);` | Crée un new processus fils |
| wait | `pid_t wait(int *status);` | Attend la fin du processus fils |
| waitpid | `pid_t waitpid(pid_t pid, int *status, int options);` | Attend un processus spécifique. |
| wait3 | `pid_t wait3(int *status, int options, struct rusage *rusage);` | Attend un processus et collecte des stat |
| wait4 | `pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);` | Comme `wait3`, mais pour un PID spécifique. |
| signal | `void (*signal(int sig, void (*handler)(int)))(int);` | Définit un gestionnaire de signal |
| sigaction | `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);` | Gestion des signaux |
| sigemptyset | `int sigemptyset(sigset_t *set);` | Initialise un ensemble vide de signaux. |
| sigaddset | `int sigaddset(sigset_t *set, int signum);` | Ajoute un signal à un ensemble. |
| kill | `int kill(pid_t pid, int sig);` | Envoie un signal à un processus. |
| getcwd | `char *getcwd(char *buf, size_t size);` | Récupère le chemin absolu du répertoire courant |
| chdir | `int chdir(const char *path);` | Change le répertoire de travail courant. |
| stat | `int stat(const char *pathname, struct stat *statbuf);` | Récupère des informations sur un fichier ou un dossier. |
| lstat | `int lstat(const char *pathname, struct stat *statbuf);` |  |
| fstat | `int fstat(int fd, struct stat *statbuf);` |  |
| unlink | `int unlink(const char *pathname);` | Supprime un fichier |
| execve | `int execve(const char *pathname, char *const argv[], char *const envp[]);` | Exécute un programme. |
| dup | `int dup(int oldfd);` | |
| dup2 | `int dup2(int oldfd, int newfd);` | |
| pipe | `int pipe(int pipefd[2]);` | Crée un canal de communication entre processus |
| opendir | `DIR *opendir(const char *name);` | Ouvre un répertoire pour lecture |
| readdir | `struct dirent *readdir(DIR *dirp);` |  |
| closedir | `int closedir(DIR *dirp);` | Ferme un répertoire ouvert. |
| isatty | `int isatty(int fd);` | Vérifie si un descripteur est un terminal |
| ttyname | `char *ttyname(int fd);` |  |
| ttyslot | `int ttyslot(void);` |  |
| ioctl | `int ioctl(int fd, unsigned long request, ...);` | |
| getenv | `char *getenv(const char *name);` | Récupère la valeur d'une variable d'environnement. |
| tcsetattr | `int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);` | |
| tcgetattr | `int tcgetattr(int fd, struct termios *termios_p);` | |
| tgetent | `int tgetent(char *bp, const char *name);` | |
| tgetflag | `int tgetflag(char *id);` |  |
| tgetnum | `int tgetnum(char *id);` |  |
| tgetstr | `char *tgetstr(char *id, char **area);` | |
| tgoto | `char *tgoto(const char *cap, int col, int row);` |  |
| tputs | `int tputs(const char *str, int affcnt, int (*putc)(int));` | |

