<h1 align="center">
#42 School - Pipex
</h1>
<p align="center">
    <img src="https://img.shields.io/github/languages/code-size/hamsathul/pipex?style=for-the-badge&&color=green">
    <img src="https://img.shields.io/github/last-commit/hamsathul/pipex?style=for-the-badge&&color=blueviolet" />
     <img src="https://img.shields.io/tokei/lines/github/hamsathul/pipex?style=for-the-badge" />
     <img src="https://img.shields.io/github/languages/count/hamsathul/pipex?style=for-the-badge&&color=orange" />     </p>

<p align="center">
 ⚠️ **Warning**: Don't copy/paste anything you don't understand: it's bad for you, and for the school.</br>
 </p>
<p>
	<b><i>Project Overview</i></b><br>
</p>
Pipex is a project at 42 school that aims to introduce students to the basics of interprocess communication and file manipulation in Unix-like 
operating systems using pipes. The goal of the project is to develop a program that can take an input file and use a series of pipes 
to manipulate the data and then output the result to an output file.

<p>
	<b><i>Learning Outcomes</i></b><br>
</p>
<ul>
<li>Familiarity with Unix-like systems</li>
<li>Understanding of interprocess communication using pipes</li>
<li>Understanding of file manipulation using file descriptors</li>
<li>Understanding of command execution using execve()</li>
</ul>


<body>
	<h2>Description</h2>
	<p>
		 This project is composed of 2 parts: the mandatory and the bonus part. The mandatory part consists of a basic pipex that takes 2 commands and 1 file and outputs the result of these commands to another file. The bonus part consists of a pipex that uses multiple pipes to execute several commands and a command that uses a "here_doc" to read data from the standard input.
		 Inside the source code the working of each function is explained as comments so the working of the program can be undersood properly.
	</p>
	<h2>Usage</h2>
	<p>
		To use pipex, you can run the compiled binary with the following format:<br>
		<pre><code>./pipex file1 cmd1 cmd2 file2</pre></code>
	</p>
	<p>
		Where:<br>
		- file1 is the input file<br>
		- cmd1 is the first command to execute<br>
		- cmd2 is the second command to execute<br>
		- file2 is the output file<br>
	</p>
	<p>
		To use pipex with the bonus part, you can do Make bonus and run compiled binary with the following format:<br>
		<pre><code>./pipex file1 cmd1 cmd2 ... cmdn file2 </pre></code>
		<p>
		Where:<br>
		- file1 is the input file<br>
		- cmd1, cmd2, ..., cmdn are the commands to execute using multiple pipes<br>
		- file2 is the output file<br>
	</p>
		<p>
	<b><i>or</i></b><br>
</p>
		<pre><code>./pipex here_doc limiter cmd1 cmd2 ... cmdn file </pre></code>
	</p>
	<p>
		Where:<br>
		- here_doc reads data from the standard input<br>
		- limiter is the limiter for here_doc<br>
		- cmd1, cmd2, ..., cmdn are the commands to execute using multiple pipes<br>
		- file is the output file<br>
	</p>

<h2>Example Commands</h2>
<p>The following are some examples of commands that can be used with the pipex program:</p>

<h3>Example 1: Single Pipe Command</h3>
<pre><code>./pipex infile "ls -l" "wc -l" outfile</code></pre>
<p>This command will read the content of 'infile', list them using the "ls -l" command and count the lines of the listed output using the "wc -l" command. The output of the "wc -l" command will be saved in 'outfile'.</p>

<h3>Example 2: Multiple Pipes Command</h3>
<pre><code>./pipex infile "ls -l" "grep a" "grep f" outfile</code></pre>
<p>This command will read the content of 'infile', list them using the "ls -l" command and filter the output using the "grep a" command. The output of the "grep a" command will then be filtered again using the "grep f" command. The final output of the "grep f" command will be saved in 'outfile'.</p>

<h3>Example 3: Here_doc and Limiter Command</h3>
<pre><code>./pipex here_doc "limiter" "grep a" "grep b" "wc -l" outfile</code></pre>
<p>when here_doc is found then data is taken in from the STDIN till the limiter is found then the input is filtered using the  "grep a" command. The output of the "grep a" command will then be filtered again using the "grep b" command which is then used by the "wc -l" command to count the number of lines. The final output of the "wc -l" command will be saved in 'outfile'.</p>
