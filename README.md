# Cifras de Beale

Um decodificador das Cifras de Beale feito em C.

Trabalho feito para a disciplina de Programação II na Universidade Federal do Paraná (UFPR) [link](https://wiki.inf.ufpr.br/maziero/doku.php?id=prog2:cifras_de_baele)

## Compilando o programa

Faça o clone do repositório:
```
git clone git@github.com:matdomis/beale-ciphers.git
```

Compile os arquivos com o comando **make**:
```
make all
```


## Contexto

De acordo com a lenda, no início do século XIX, um homem chamado Thomas J. Beale enterrou um tesouro no valor de milhões de dólares em algum lugar da Virgínia. Beale deixou três textos cifrados com um dono de hotel, Robert Morriss, antes de desaparecer, e instruiu Morriss a abrir o pacote contendo as cifras apenas se ele não retornasse dentro de 10 anos. O primeiro texto cifrado descreve o conteúdo do tesouro, enquanto os outros dois descrevem a localização exata do local de enterro. Apesar de muitas tentativas de decodificar as cifras, seu significado permanece um mistério até hoje. A Figura 1 abaixo mostra um dos textos cifrados.

![imagem](https://wiki.inf.ufpr.br/maziero/lib/exe/fetch.php?w=600&tok=f24680&media=prog2:cifra.png)

Acredita-se que os textos cifrados foram criados usando um livro cifra, que é um tipo de criptografia que usa um livro ou texto pré-acordado como chave. Em um livro cifra, a mensagem em texto simples é primeiro convertida em números, e então cada número é usado para referenciar uma palavra ou frase específica no livro. A sequência resultante de palavras ou frases se torna o texto cifrado, como o exemplo da Figura 1. (Para mais detalhes, https://en.wikipedia.org/wiki/Beale_ciphers)

## Gerando as cifras

Beale usou uma variante de um livro cifra. Ele escolheu um texto longo como texto cifra, numerou cada uma das palavras do texto sequencialmente, começando em 0 (zero), e formou uma nova mensagem em que cada caracter desta mensagem é a primeira letra de alguma palavra do texto cifra. A mensagem codificada final consiste em uma lista dos números de sequência das palavras escolhidas.

Considere por exemplo o seguinte texto como livro cifra:

```
"Em 1892 o intelectual paranaense José Francisco da Rocha Pombo colocaria, no Largo Ouvidor Pardinho, a pedra fundamental da Universidade do Paraná. O projeto foi frustrado pelo Movimento Federalista que impediu a 
criação da universidade.Vinte anos depois, em 1912, o estado contava com um reduzido número de intelectuais, 
apenas nove médicos e quatro engenheiros, mas se desenvolvia muito devido a produção da erva-mate. Além 
disso, a Guerra do Contestado fez com que as vastas lideranças políticas se empenhassem pela criação de 
uma universidade, de modo a dar uma identidade ao povo paranaense."
```

Usando a ideia de Beale, (considerando que apenas espaço e linefeed (mudança de linha) são usados para separar palavras) teríamos arquivo de chaves abaixo, em que cada linha contém 2 campos separados por ‘:’ . O segundo campo contém uma lista da posição de palavras cuja primeiro caracter é o caracter indicado no primeiro campo.

```
1: 38 1 
a: 89 85 72 65 63 59 48 35 31 15 
c: 79 70 68 42 41 32 10 
d: 86 83 80 67 64 61 58 56 46 36 33 20 18 7 
e: 77 62 53 51 40 37 0 
f: 69 28 25 24 17 6 
g: 66 
i: 88 47 30 3 
j: 5 
l: 74 12 
m: 84 57 54 50 27 
n: 49 45 11 
o: 39 22 13 2 
p: 91 90 78 75 60 26 23 21 16 14 9 4 
q: 71 52 29 
r: 44 8 
s: 76 55 
u: 87 82 81 43 34 19 
v: 73 
```

Usando os códigos acima, a frase **“casa de papel”** poderia ser codificada da seguinte maneira:

```
42 15 76 85 -1 46 51 -1 91 48 75 77 12
```

Ou ainda:

```
79 85 55 72 -1 64 62 -1 90 89 90 0 12 
```

Note que no exemplo acima, algumas letras são representadas por vários códigos. Quanto maior o livro cifra, mais cchaves serão atribuídos para a mesma letra, aumentando assim o número de representações possíveis do texto cifrado. Ainda no exemplo acima, vale mencionar que o espaço entre as palavras foi representado pelo código -1.

## Implementação

Escreva um programa em C que codifique e decodifique uma mensagem usando a cifra de Beale. O programa deverá ter as seguintes funcionalidades:

- Codificar uma mensagem qualquer contida em um arquivo ASCII usando um livro cifra. O programa deve ter uma opção de salvar em um arquivo texto as chaves geradas no formato descrito anteriormente. A linha de execução do programa dever ser a seguinte:

```
./beale  -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves 
```

- Decodificar uma mensagem, usando um arquivo de códigos

```
./beale  -d  -i MensagemCodificada  -c ArquivoDeChaves  -o MensagemDecodificada 
```

- Decodificar uma mensagem usando o livro cifra

```
./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada 
```

