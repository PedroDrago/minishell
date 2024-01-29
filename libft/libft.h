/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:53:29 by pdrago            #+#    #+#             */
/*   Updated: 2024/01/27 04:23:10 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include "list/list.h"
# include "stack/stack.h"
# include "queue/queue.h"
# include "hashmap/hashmap.h"
# include "get_next_line/get_next_line.h"

# ifndef INT_MIN
#  define INT_MIN -2147483648
# endif 

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif 

# ifndef UINT_MAX
#  define UINT_MAX 4294967295
# endif

# ifndef LONG_MAX
#  define LONG_MAX 9223372036854775807
# endif

# ifndef LONG_MIN
#  define LONG_MIN -9223372036854775808
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

/*
Converts the initial portion of the string pointed 
to by `str` to `int`. The number in the string can 
be in any base up to 16, and the charset used will be the 
hexadecimal (`0123456789abcdef`). The string can be in any case.
*/
int		ft_atoi_base(const char *str, int base, const char *charset);
/*
If  `c`  is  a  lowercase  letter, `ft_toupper()`
returns its uppercase equivalent.
*/
int		ft_toupper(int c);
/*
If `c` is an uppercase letter, `ft_tolower()`
returns its lowercase equivalent.
*/
int		ft_tolower(int c);
//Checks for any printable character including space.
int		ft_isprint(int c);
//Checks for a digit (`0` through `9`).
int		ft_isdigit(int c);
/*
Checks whether `c` is a 7-bit `unsigned char` value 
that fits into the ASCII character set.
*/
int		ft_isascii(int c);
/*
Checks  for  an  alphabetic  character, it is 
equivalent to (`ft_isupper(c)` || `ft_islower(c)`).
*/
int		ft_isalpha(int c);
/*
Checks for an alphanumeric character, 
it is equivalent to (`ft_isalpha(c)` || `ft_isdigit(c)`).
*/
int		ft_isalnum(int c);
/*
Converts the initial portion of the string pointed 
to by `nptr` to `int`. The string may begin with arbitrary amount of whitespace
determined by isspace(3), followed by a single optional `+` or `-` sign.
*/
int		ft_atoi(const char *nptr);
/*
Compare the two strings `s1` and `s2`, but 
only the first (at most) `n` bytes of `s1` and `s2`.  

       Returns an integer indicating the result 
       of the comparison, as follows:
       - `0`, if the `s1` and `s2` are equal;
       - a negative value if `s1` is less than `s2`;
       - a positive value if `s1 is greater than `s2`.
*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/*
Returns an integer less than, equal 
to, or greater than zero if the first `n` bytes of `s1` is found, 
respectively, to be less than, to match, or be greater than the 
first `n` bytes of `s2`.

For a nonzero return value, the sign is determined by the sign of the 
difference between the first pair of bytes (interpreted as unsigned char) 
that differ in `s1` and `s2`.

If `n` is zero, the return value is zero.
*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/*
Returns the index of the 
first occurrence of the character `c` in the string `s`.

If the character is not found it returns -1.
*/
int		ft_strchr_idx(const char *str, char c);
//Searches for the `wanted` in an ordered `int` array.
int		ft_binary_search(int size, int array[], int wanted);
/*
Calculates and returns the length of the 
string pointed to by `s`, excluding the terminating null byte (`\0`).
*/
size_t	ft_strlen(const char *s);
/*
Copies up to `size` - 1 characters from the NUL-terminated `src` 
string to the `dst` string, NUL-terminating the result.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
/*
Appends at most `size` - `ft_strlen(dst - 1)` bytes from the
NUL-terminated `src string to the end of the `dst` string.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size);
//Allocate with malloc() a reversed version of the string `src`
char	*ft_strrev(const char *str);
/*
Locates the first occurrence of the 
null-terminated string `little` in the string `big`, where not 
more than `len` characters are searched.  Characters that appear 
after a `\0` character are not searched.
*/
char	*ft_strnstr(const char *big, const char *little, size_t len);
/*
Returns a pointer to the last 
occurrence of the character `c` in the string `s`.
*/
char	*ft_strrchr(const char *s, int c);
/*
Function returns a pointer to the
first occurrence of the character `c` in the string `s`.
*/
char	*ft_strchr(const char *s, int c);
/*
Returns a pointer to a new string which is a 
duplicate of the string `s`.  Memory for the new string is obtained with 
malloc(3), and can be freed with free(3).
*/
char	*ft_strdup(const char *s);
/*
Allocates (with malloc(3)) and returns a substring
from the string `s`.
The substring begins at index `start` and is of
maximum size `len`.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
/*
Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of `s1` and `s2`.

If flag is passed as `1` it will free `s1`
If flag is passed as `2` it will free `s2`
If flag is passed as `3` it will free both `s1 and `s2`
Otherwise it won't free any string
*/
char	*ft_strjoin(char const *s1, char const *s2, int should_free);
/*
Allocates (with malloc(3)) and returns a copy of
`s1` with the characters specified in `set` removed
from the beginning and the end of the string.
*/
char	*ft_strtrim(char const *s1, char const *set);
/*
Allocates (with malloc(3)) and returns an array
of strings obtained by splitting `s` using the
character `c` as a delimiter. The array must end
with a NULL pointer
*/
char	**ft_split(char const *s, char c);
/*
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
*/
char	*ft_itoa(int n);
/*
Applies the function `f` to each character of the
string `s`, and passing its index as first argument
to create a new string (with malloc(3)) resulting
from successive applications of `f`.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/*
Fills the first n bytes 
of the memory area pointed to by `s` with the constant byte `c`.
*/
void	*ft_memset(void *s, int c, size_t n);
/*
Copies n bytes from memory area 
`src` to memory area `dest`.  The memory areas must not overlap.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n);
/*
Erases the data in the `n` bytes of the 
memory starting at the location pointed to 
by `s`, by writing zeros (bytes containing `\0`) to that area.
*/
void	ft_bzero(void *s, size_t n);
/*
Scans the initial `n` bytes of the memory area 
pointed to by `s` for the first instance of `c`.  Both c and the bytes of 
the memory area pointed to by `s` are interpreted as `unsigned char`.
*/
void	*ft_memchr(const void *s, int c, size_t n);
/*
Allocates memory for an array of `nmemb` elements 
of `size`  bytes each  and  returns a pointer to 
the allocated memory. The memory is set to zero. 
If `nmemb` or `size` is 0, then calloc() returns 
either `NULL`, or a unique pointer value that can 
later be successfully passed 
to `free()`. If the multiplication of `nmemb` and 
`size` would result in integer 
overflow, then calloc() returns an error.
*/
void	*ft_calloc(size_t nmemb, size_t size);
/*
Copies `n` bytes from the `src` memory area to the `dst`
memory area. The areas may overlap.
*/
void	*ft_memmove(void *dest, const void *src, size_t n);
/*
Applies the function `f` on each character of
the string `s`, passing its index
as first argument. Each character is passed by
address to `f` to be modified if necessary.
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/*
Outputs the character `c` to the given file
descriptor.
*/
void	ft_putchar_fd(char c, int fd);
/*
Outputs the string `s` to the given file
descriptor.
*/
void	ft_putstr_fd(char *s, int fd);
/*
Outputs the string `s` to the given file descriptor
followed by a newline.
*/
void	ft_putendl_fd(char *s, int fd);
/*
Outputs the integer `n` to the given file
descriptor
*/
void	ft_putnbr_fd(int n, int fd);
/*
Set all characters from string `str` to uppercase
*/
void	ft_strupper(char *str);
/*
Set all characters from string `str` to lowercase
*/
void	ft_strlower(char *str);
/*
* Converts the initial portion of the string pointed 
* to by `nptr` to `long`. The string may begin with
* arbitrary amount of whitespace
* determined by `isspace(3)`, followed by a single
* optional `+` or `-` sign.
*/
long	ft_atol(const char *nptr);

#endif
