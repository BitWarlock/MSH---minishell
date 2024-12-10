#include <dirent.h>
#include <libc.h>

int	suffix_match(char *entry, char *pattern);

int	is_hidden(char first, char *entry)
{
	if (first == '.' && entry[0] == '.')
		return (1);
	return (!(first != '.' && entry[0] == '.'));
}

int	pattern_match(char *entry, char *pattern)
{
	while (*entry && *pattern)
	{
		if (*pattern == '*')
			return (suffix_match(entry, pattern + 1));
		if (*pattern != *entry)
			return (0);
		entry++;
		pattern++;
	}
	return ((*pattern == '\0' || *pattern == '*')
		&& *entry == '\0');
}

int	suffix_match(char *entry, char *pattern)
{
	if (*pattern == '\0')
		return (1);
	while (*entry)
	{
		if (pattern_match(entry, pattern))
			return (1);
		entry++;
	}
	return (0);
}

int	entry_count(char *pattern)
{
	struct dirent	*entry;
	int				count;
	DIR				*current;

	current = opendir(".");
	if (!current)
		return (-1);
	count = 0;
	entry = readdir(current);
	while (entry)
	{
		if (pattern_match(entry->d_name, pattern))
			if (is_hidden(pattern[0], entry->d_name))
				count++;
		entry = readdir(current);
	}
	closedir(current);
	return (count);
}

int	new_args_count(char **args)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (strchr(args[i], '*'))
			count += entry_count(args[i]);
		else
			count++;
		i++;
	}
	return (count);
}

void	expand_arg(char **new, int *args_i, char *pattern)
{
	struct dirent	*entry;
	DIR				*current;

	current = opendir(".");
	if (!current)
		return ;
	entry = readdir(current);
	while (entry)
	{
		if (pattern_match(entry->d_name, pattern))
		{
			if (is_hidden(pattern[0], entry->d_name))
				new[(*args_i)++] = strdup(entry->d_name);
		}
		entry = readdir(current);
	}
	closedir(current);
}

char	**expand_wildcard(char **old)
{
	char	**new;
	int		args_size;
	int		args_i;
	int		i;

	args_size = new_args_count(old);
	if (!args_size)
		return (old);
	i = -1;
	args_i = 0;
	new = malloc(sizeof(char *) * (args_size + 2));
	while (old[++i])
	{
		if (!strchr(old[i], '*')
			|| old[i][0] == '\'' || old[i][0] == '"'
			|| !entry_count(old[i]))
			new[args_i++] = strdup(old[i]);
		else
			expand_arg(new, &args_i, old[i]);
	}
	new[args_i] = NULL;
	return (new);
}

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	is_1valid(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

int	ft_isnum(char c)
{
	return (c >= '0' && c <= '9');
}

char	*remove_quotes(char *str)
{
	size_t	i;
	size_t	j;
	char	c;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '"'
			|| str[i] == '\'')
		{
			c = str[i++];
			while (str[i] != c)
				new[j++] = str[i++];
			i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}

char	**remove_all_quotes(char **old)
{
	int	i;

	i = 0;
	while (old[i])
	{
		if (old[i])
			old[i] = remove_quotes(old[i]);
		i++;
	}
	return (old);
}

int	is_valid_env(char c)
{
	return (is_1valid(c) || ft_isnum(c));
}

char	*get_env_value(char *val, t_env *env)
{
	while (env)
	{
		if (!strncmp(val, env->name, strlen(val)))
			return (strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*expand_var(char *ret, int *i, char *s, t_env *env)
{
	char	*env_var;
	int		env_size;

	(*i)++;
	env_size = *i;
	if (s[env_size] == '?')
		return ((*i)++,
			ft_strjoin(ret, ft_itoa(exit_status(GET, 0))));
	while (is_valid_env(s[env_size]))
		env_size++;
	env_size -= *i;
	env_var = ft_substr(s, *i, env_size);
	env_var = get_env_value(env_var, env);
	*i += env_size;
	if (!env_var)
		return (ret);
	ret = ft_strjoin(ret, env_var);
	return (ret);
}

char	*double_q_fill(char *ret, char *s, int *i, t_env **env)
{
	ret = join_char(ret, s[(*i)++]);
	while (s[*i])
	{
		if (s[*i] == '$' && is_1valid(s[(*i) + 1]))
			ret = expand_var(ret, i, s, *env);
		else if (s[*i] == '"')
		{
			ret = join_char(ret, s[(*i)++]);
			break ;
		}
		else
			ret = join_char(ret, s[(*i)++]);
	}
	return (ret);
}

char	*single_q_fill(char *ret, char *s, int *i)
{
	while (s[*i])
	{
		ret = join_char(ret, s[(*i)++]);
		if (s[*i] == '\'')
		{
			ret = join_char(ret, s[(*i)++]);
			return (ret);
		}
	}
	return (ret);
}

char	*switch_in_single_q(char *str)
{
	int		i;
	char	*new;

	new = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), MAL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			new[i] = str[i];
			while (str[++i] != '\'')
			{
				if (str[i] == ' ')
					new[i] = -1;
				else if (str[i] == '\t')
					new[i] = -2;
				else if (str[i] == '"')
					new[i] = -3;
				else
					new[i] = str[i];
			}
		}
		new[i] = str[i];
	}
	return (new[i] = 0, new);
}

char	*switch_in_double_q(char *str)
{
	char	*new;
	int		i;

	new = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), MAL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			new[i] = str[i];
			while (str[++i] != '"')
			{
				if (str[i] == ' ')
					new[i] = -1;
				else if (str[i] == '\t')
					new[i] = -2;
				else
					new[i] = str[i];
			}
		}
		new[i] = str[i];
	}
	new[i] = '\0';
	return (new);
}

char	*switch_back(char *str)
{
	int		i;
	char	*new;

	new = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), MAL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == -1)
			new[i] = ' ';
		else if (str[i] == -2)
			new[i] = '\t';
		else if (str[i] == -3)
			new[i] = '"';
		else
			new[i] = str[i];
	}
	new[i] = '\0';
	return (new);
}

void	format_and_split(char *result, t_tree *node)
{
	int		i;
	char	**new;

	i = 0;
	result = switch_in_single_q(result);
	result = switch_in_double_q(result);
	new = ft_split(result, " \t");
	while (new[i])
	{
		new[i] = switch_back(new[i]);
		i++;
	}
	node->cmd = remove_all_quotes(expand_wildcard(new));
}

void	expand_cmd(t_tree *node, t_env **env)
{
	int		i;
	char	*result;
	char	*n;

	result = ft_strdup("");
	n = node->p_cmd;
	i = 0;
	while (n[i])
	{
		if (n[i] == '\'')
			result = single_q_fill(result, n, &i);
		else if (n[i] == '"')
			result = double_q_fill(result, n, &i, env);
		else if (n[i] == '$' && is_1valid(n[i + 1]))
			result = expand_var(result, &i, n, *env);
		else if (n[i] == '$' && (n[i + 1] == '"' || n[i + 1] == '\''))
			i++;
		else
			result = join_char(result, n[i++]);
	}
	format_and_split(result, node);
	for (int i = 0; node->cmd[i]; i++)
	{
		printf("%d: %s\n", i, node->cmd[i]);
	}
}
