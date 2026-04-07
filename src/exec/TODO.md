- exec-core (AST walker) : DONE

- exec-cmd (Node-cmd handler, forks and dispatches) : DONE

- exec-pipe (Node-pipe handle) : DONE

- exec-logical (Node-and Node-or handler) : DONE

- exec-builtin (builtin detection and dispatch through table) : DONE

- exec-external (execve + PATH resolution) : DONE

- exec-redir (apply < > >> before execution) : DONE

- exec-expand : WORK IN PROGRESS (see TODO in the file)

- exec-heredoc (<< handling) :

- exec-fd (save, restore fds for builtin running in parent process) :

- exec-wait (waitpid + store result in ctx return-code) :

- exec-error (handle command not found, permission denied and such) :

    - exec.h:
        - exec-core : DONE
        - exec-cmd : DONE
        - exec-pipe : DONE
        - exec-logical : DONE
        - exec-builtin : DONE
        - exec-external : DONE
        - exec-redir : DONE
        - exec-expand : WORK IN PROGRESS (see TODO in the file)
        - exec-heredoc :
        - exec-fd :
        - exec-wait :
        - exec-error :

- norminette :
