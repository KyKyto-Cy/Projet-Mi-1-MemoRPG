
#  Makefile — MemoRPG

 
# Compilateur et options
CC      = gcc
CFLAGS  = -Wall -Wextra -g
# -Wall   : active tous les warnings courants
# -Wextra : active des warnings supplémentaires
# -g      : inclut les infos de débogage (utile avec gdb)
 
# Nom du binaire final
NAME    = memo_rpg
 
# Dossiers
SRC_DIR = src
OBJ_DIR = obj
 
# Récupère automatiquement tous les fichiers .c dans src
SRCS    = $(wildcard $(SRC_DIR)/*.c)
 
# Transforme chaque src/xxx.c en obj/xxx.o
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
 

#  Règle principale : compiler tout

all: $(NAME)
 
# Lier tous les .o pour produire le binaire
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "✅ Compilation réussie : ./$(NAME)"
 
# Compiler chaque .c en .o (crée le dossier obj/ si besoin)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
 

#  Lancer le jeu

run: all
	./$(NAME)
 

#  Nettoyage

 
# Supprime les fichiers objets
clean:
	rm -rf $(OBJ_DIR)
	@echo "🧹 Fichiers objets supprimés"
 
# Supprime tout (objets + binaire)
fclean: clean
	rm -f $(NAME)
	@echo "🗑️  Binaire supprimé"
 
# Recompile tout from scratch
re: fclean all
 
# Ces règles ne correspondent pas à des fichiers réels
.PHONY: all run clean fclean re