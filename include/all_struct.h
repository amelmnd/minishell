#ifndef ALL_STRUCT_H
# define ALL_STRUCT_H

enum	E_BOOL
{
	TRUE 1,
	FALSE 0
}

enum	E_LEXER_TYPE
{
	PIPE, // |
	WORD,
	S_QUOTE, // ' '
	D_QUOTE, // " "
	R_REDIRECT // <
	HEREDOC, // <<
	W_REDIRECT // >
	W_APPEND_REDIRECT // >>
	BLANK, // space tab
	VARIABLE, // $text tout ce qui commence par un $. sauf $?
	RETURN_VALUE, // $?
	SPECIAL_VAR, // $non alpha
}

struct	E_EXPEND_TYPE
{
	previous;
	next;
	enum E_LEXER_TYPE;
	char *str;
	char *env_name; //tout str de type $cara alpha
	// pour avoir le nom pour le heredoc
	char *env_value; //recu step 1 expendeur
	//pour recupere la valeur sans ecraser le nom
}

enum E_EXPEND_TYPE
{
	WORD,
	R_ORIGIN_REDIRECT
	LIMITER_HEREDOC,
	W_DEST_REDIRECT,
	WA_DEST_REDIRECT
}

struct parser_list
{
	previous;
	next;
	enum E_EXPEND_TYPE; // 
	char *str;
}

struct s_redirect
{
	enum E_EXPEND_TYPE;
	char *value;
} t_redirect;

struct s_for_exec
{
	previous;
	next;
	char *cmd;
	char **arg_array;
	t_redirect *redirect_array;
}

#endif