/* The keys organised in this file follow a scheme of uppercase ascii as the Higer byte and lowercase ascii as the lower byte of the pressed key
   I have chosen this method because most character keys have an alternative of 2, with the second character got after pressing the shift key
*/

	.code32
	.global ascii_keys

	
	.data
	
ascii_keys:	
a_key: .word 0x4161
b_key: .word 0x4262
c_key: .word 0x4363
d_key: .word 0x4464
e_key: .word 0x4565
f_key: .word 0x4666
g_key: .word 0x4767
h_key: .word 0x4868
i_key: .word 0x4969
j_key: .word 0x4a6a
k_key: .word 0x4b6b
l_key: .word 0x4c6c
m_key: .word 0x4d6d
n_key: .word 0x4e6e
o_key: .word 0x4f6f
p_key: .word 0x5070
q_key: .word 0x5171
r_key: .word 0x5272
s_key: .word 0x5373
t_key: .word 0x5474
u_key: .word 0x5575
v_key: .word 0x5676
w_key: .word 0x5777
x_key: .word 0x5878
y_key: .word 0x5979
z_key: .word 0x5a7a

