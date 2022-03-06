	.code32
	.global terminal_main
	.text

terminal_main:

	push $prompt_str
	call puts


	.data

prompt_str:	.asciz "impala> "
