
ej6:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 7a 2f 00 00    	push   0x2f7a(%rip)        # 3fa0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 7c 2f 00 00    	jmp    *0x2f7c(%rip)        # 3fa8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nopl   0x0(%rax)
    1030:	f3 0f 1e fa          	endbr64
    1034:	68 00 00 00 00       	push   $0x0
    1039:	e9 e2 ff ff ff       	jmp    1020 <_init+0x20>
    103e:	66 90                	xchg   %ax,%ax
    1040:	f3 0f 1e fa          	endbr64
    1044:	68 01 00 00 00       	push   $0x1
    1049:	e9 d2 ff ff ff       	jmp    1020 <_init+0x20>
    104e:	66 90                	xchg   %ax,%ax
    1050:	f3 0f 1e fa          	endbr64
    1054:	68 02 00 00 00       	push   $0x2
    1059:	e9 c2 ff ff ff       	jmp    1020 <_init+0x20>
    105e:	66 90                	xchg   %ax,%ax
    1060:	f3 0f 1e fa          	endbr64
    1064:	68 03 00 00 00       	push   $0x3
    1069:	e9 b2 ff ff ff       	jmp    1020 <_init+0x20>
    106e:	66 90                	xchg   %ax,%ax
    1070:	f3 0f 1e fa          	endbr64
    1074:	68 04 00 00 00       	push   $0x4
    1079:	e9 a2 ff ff ff       	jmp    1020 <_init+0x20>
    107e:	66 90                	xchg   %ax,%ax

Disassembly of section .plt.got:

0000000000001080 <__cxa_finalize@plt>:
    1080:	f3 0f 1e fa          	endbr64
    1084:	ff 25 6e 2f 00 00    	jmp    *0x2f6e(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    108a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001090 <__stack_chk_fail@plt>:
    1090:	f3 0f 1e fa          	endbr64
    1094:	ff 25 16 2f 00 00    	jmp    *0x2f16(%rip)        # 3fb0 <__stack_chk_fail@GLIBC_2.4>
    109a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000010a0 <printf@plt>:
    10a0:	f3 0f 1e fa          	endbr64
    10a4:	ff 25 0e 2f 00 00    	jmp    *0x2f0e(%rip)        # 3fb8 <printf@GLIBC_2.2.5>
    10aa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000010b0 <pthread_exit@plt>:
    10b0:	f3 0f 1e fa          	endbr64
    10b4:	ff 25 06 2f 00 00    	jmp    *0x2f06(%rip)        # 3fc0 <pthread_exit@GLIBC_2.2.5>
    10ba:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000010c0 <pthread_create@plt>:
    10c0:	f3 0f 1e fa          	endbr64
    10c4:	ff 25 fe 2e 00 00    	jmp    *0x2efe(%rip)        # 3fc8 <pthread_create@GLIBC_2.34>
    10ca:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000010d0 <pthread_join@plt>:
    10d0:	f3 0f 1e fa          	endbr64
    10d4:	ff 25 f6 2e 00 00    	jmp    *0x2ef6(%rip)        # 3fd0 <pthread_join@GLIBC_2.34>
    10da:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000000010e0 <_start>:
    10e0:	f3 0f 1e fa          	endbr64
    10e4:	31 ed                	xor    %ebp,%ebp
    10e6:	49 89 d1             	mov    %rdx,%r9
    10e9:	5e                   	pop    %rsi
    10ea:	48 89 e2             	mov    %rsp,%rdx
    10ed:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    10f1:	50                   	push   %rax
    10f2:	54                   	push   %rsp
    10f3:	45 31 c0             	xor    %r8d,%r8d
    10f6:	31 c9                	xor    %ecx,%ecx
    10f8:	48 8d 3d 73 01 00 00 	lea    0x173(%rip),%rdi        # 1272 <main>
    10ff:	ff 15 d3 2e 00 00    	call   *0x2ed3(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1105:	f4                   	hlt
    1106:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    110d:	00 00 00 

0000000000001110 <deregister_tm_clones>:
    1110:	48 8d 3d f9 2e 00 00 	lea    0x2ef9(%rip),%rdi        # 4010 <__TMC_END__>
    1117:	48 8d 05 f2 2e 00 00 	lea    0x2ef2(%rip),%rax        # 4010 <__TMC_END__>
    111e:	48 39 f8             	cmp    %rdi,%rax
    1121:	74 15                	je     1138 <deregister_tm_clones+0x28>
    1123:	48 8b 05 b6 2e 00 00 	mov    0x2eb6(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    112a:	48 85 c0             	test   %rax,%rax
    112d:	74 09                	je     1138 <deregister_tm_clones+0x28>
    112f:	ff e0                	jmp    *%rax
    1131:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1138:	c3                   	ret
    1139:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001140 <register_tm_clones>:
    1140:	48 8d 3d c9 2e 00 00 	lea    0x2ec9(%rip),%rdi        # 4010 <__TMC_END__>
    1147:	48 8d 35 c2 2e 00 00 	lea    0x2ec2(%rip),%rsi        # 4010 <__TMC_END__>
    114e:	48 29 fe             	sub    %rdi,%rsi
    1151:	48 89 f0             	mov    %rsi,%rax
    1154:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1158:	48 c1 f8 03          	sar    $0x3,%rax
    115c:	48 01 c6             	add    %rax,%rsi
    115f:	48 d1 fe             	sar    $1,%rsi
    1162:	74 14                	je     1178 <register_tm_clones+0x38>
    1164:	48 8b 05 85 2e 00 00 	mov    0x2e85(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    116b:	48 85 c0             	test   %rax,%rax
    116e:	74 08                	je     1178 <register_tm_clones+0x38>
    1170:	ff e0                	jmp    *%rax
    1172:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1178:	c3                   	ret
    1179:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001180 <__do_global_dtors_aux>:
    1180:	f3 0f 1e fa          	endbr64
    1184:	80 3d 85 2e 00 00 00 	cmpb   $0x0,0x2e85(%rip)        # 4010 <__TMC_END__>
    118b:	75 2b                	jne    11b8 <__do_global_dtors_aux+0x38>
    118d:	55                   	push   %rbp
    118e:	48 83 3d 62 2e 00 00 	cmpq   $0x0,0x2e62(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1195:	00 
    1196:	48 89 e5             	mov    %rsp,%rbp
    1199:	74 0c                	je     11a7 <__do_global_dtors_aux+0x27>
    119b:	48 8b 3d 66 2e 00 00 	mov    0x2e66(%rip),%rdi        # 4008 <__dso_handle>
    11a2:	e8 d9 fe ff ff       	call   1080 <__cxa_finalize@plt>
    11a7:	e8 64 ff ff ff       	call   1110 <deregister_tm_clones>
    11ac:	c6 05 5d 2e 00 00 01 	movb   $0x1,0x2e5d(%rip)        # 4010 <__TMC_END__>
    11b3:	5d                   	pop    %rbp
    11b4:	c3                   	ret
    11b5:	0f 1f 00             	nopl   (%rax)
    11b8:	c3                   	ret
    11b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000011c0 <frame_dummy>:
    11c0:	f3 0f 1e fa          	endbr64
    11c4:	e9 77 ff ff ff       	jmp    1140 <register_tm_clones>

00000000000011c9 <incl>:
    11c9:	55                   	push   %rbp
    11ca:	48 89 e5             	mov    %rsp,%rbp
    11cd:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    11d1:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    11d5:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    11d9:	ff 00                	incl   (%rax)
    11db:	90                   	nop
    11dc:	5d                   	pop    %rbp
    11dd:	c3                   	ret

00000000000011de <incl2>:
    11de:	55                   	push   %rbp
    11df:	48 89 e5             	mov    %rsp,%rbp
    11e2:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    11e6:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    11ea:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    11ee:	f0 ff 00             	lock incl (%rax)
    11f1:	90                   	nop
    11f2:	5d                   	pop    %rbp
    11f3:	c3                   	ret

00000000000011f4 <inc1>:
    11f4:	f3 0f 1e fa          	endbr64
    11f8:	55                   	push   %rbp
    11f9:	48 89 e5             	mov    %rsp,%rbp
    11fc:	48 83 ec 20          	sub    $0x20,%rsp
    1200:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    1204:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    120b:	eb 13                	jmp    1220 <inc1+0x2c>
    120d:	48 8d 05 04 2e 00 00 	lea    0x2e04(%rip),%rax        # 4018 <num>
    1214:	48 89 c7             	mov    %rax,%rdi
    1217:	e8 ad ff ff ff       	call   11c9 <incl>
    121c:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
    1220:	81 7d fc e7 03 00 00 	cmpl   $0x3e7,-0x4(%rbp)
    1227:	7e e4                	jle    120d <inc1+0x19>
    1229:	bf 00 00 00 00       	mov    $0x0,%edi
    122e:	e8 7d fe ff ff       	call   10b0 <pthread_exit@plt>

0000000000001233 <inc2>:
    1233:	f3 0f 1e fa          	endbr64
    1237:	55                   	push   %rbp
    1238:	48 89 e5             	mov    %rsp,%rbp
    123b:	48 83 ec 20          	sub    $0x20,%rsp
    123f:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    1243:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    124a:	eb 13                	jmp    125f <inc2+0x2c>
    124c:	48 8d 05 c5 2d 00 00 	lea    0x2dc5(%rip),%rax        # 4018 <num>
    1253:	48 89 c7             	mov    %rax,%rdi
    1256:	e8 83 ff ff ff       	call   11de <incl2>
    125b:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
    125f:	81 7d fc e7 03 00 00 	cmpl   $0x3e7,-0x4(%rbp)
    1266:	7e e4                	jle    124c <inc2+0x19>
    1268:	bf 00 00 00 00       	mov    $0x0,%edi
    126d:	e8 3e fe ff ff       	call   10b0 <pthread_exit@plt>

0000000000001272 <main>:
    1272:	f3 0f 1e fa          	endbr64
    1276:	55                   	push   %rbp
    1277:	48 89 e5             	mov    %rsp,%rbp
    127a:	48 83 ec 20          	sub    $0x20,%rsp
    127e:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1285:	00 00 
    1287:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    128b:	31 c0                	xor    %eax,%eax
    128d:	48 8d 45 e8          	lea    -0x18(%rbp),%rax
    1291:	b9 00 00 00 00       	mov    $0x0,%ecx
    1296:	48 8d 15 57 ff ff ff 	lea    -0xa9(%rip),%rdx        # 11f4 <inc1>
    129d:	be 00 00 00 00       	mov    $0x0,%esi
    12a2:	48 89 c7             	mov    %rax,%rdi
    12a5:	e8 16 fe ff ff       	call   10c0 <pthread_create@plt>
    12aa:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    12ae:	b9 00 00 00 00       	mov    $0x0,%ecx
    12b3:	48 8d 15 79 ff ff ff 	lea    -0x87(%rip),%rdx        # 1233 <inc2>
    12ba:	be 00 00 00 00       	mov    $0x0,%esi
    12bf:	48 89 c7             	mov    %rax,%rdi
    12c2:	e8 f9 fd ff ff       	call   10c0 <pthread_create@plt>
    12c7:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    12cb:	be 00 00 00 00       	mov    $0x0,%esi
    12d0:	48 89 c7             	mov    %rax,%rdi
    12d3:	e8 f8 fd ff ff       	call   10d0 <pthread_join@plt>
    12d8:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    12dc:	be 00 00 00 00       	mov    $0x0,%esi
    12e1:	48 89 c7             	mov    %rax,%rdi
    12e4:	e8 e7 fd ff ff       	call   10d0 <pthread_join@plt>
    12e9:	8b 05 29 2d 00 00    	mov    0x2d29(%rip),%eax        # 4018 <num>
    12ef:	89 c6                	mov    %eax,%esi
    12f1:	48 8d 05 0c 0d 00 00 	lea    0xd0c(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    12f8:	48 89 c7             	mov    %rax,%rdi
    12fb:	b8 00 00 00 00       	mov    $0x0,%eax
    1300:	e8 9b fd ff ff       	call   10a0 <printf@plt>
    1305:	b8 00 00 00 00       	mov    $0x0,%eax
    130a:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    130e:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    1315:	00 00 
    1317:	74 05                	je     131e <main+0xac>
    1319:	e8 72 fd ff ff       	call   1090 <__stack_chk_fail@plt>
    131e:	c9                   	leave
    131f:	c3                   	ret

Disassembly of section .fini:

0000000000001320 <_fini>:
    1320:	f3 0f 1e fa          	endbr64
    1324:	48 83 ec 08          	sub    $0x8,%rsp
    1328:	48 83 c4 08          	add    $0x8,%rsp
    132c:	c3                   	ret
