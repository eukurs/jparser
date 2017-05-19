/*
 ============================================================================
 Name        : teste_db.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//#include <stdio.h>
//#include <stdlib.h>
//
//int main(void) {
//	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
//	return EXIT_SUCCESS;
//}

#include <mysql.h>
#include <stdio.h>

int main(void)
{
      MYSQL conexao;
      MYSQL_RES *resposta;
      MYSQL_ROW linhas;
      MYSQL_FIELD *campos;
      int query_code;
      char query[]="SELECT * FROM aprendendo;";
      //char query[]="truncate aprendendo;";
      //char query[]="INSERT INTO aprendendo(nome,sexo) values('Caio Fernando Soares', 'M')";
      mysql_init(&conexao);
      if ( mysql_real_connect(&conexao, "localhost", "guest", "guest", "teste", 0, NULL, 0) )
      {
            printf("conectado com sucesso!\n");
            //res=mysql_query(&conexao,"INSERT INTO aprendendo(nome,sexo) values('Caio Fernando Soares', 'M')");
            query_code=mysql_query(&conexao,query);
            if (!query_code)
            {
            	resposta=mysql_store_result(&conexao);
            	printf("Registros inseridos %d\n", mysql_affected_rows(&conexao));
            }else {
            	printf("Erro na inserção %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
            }
            if(resposta)
            {
            	campos=mysql_fetch_fields(resposta);
            	for(int i=0;i<mysql_num_fields(resposta); i++)
            	{
            		printf("%s\t",(campos[i]).name);
            	}
            	printf("\n");
            	while((linhas=mysql_fetch_row(resposta))!= NULL)
            	{
            		for(int i=0;i<mysql_num_fields(resposta);i++)
            		{
            			printf("%s\t", linhas[i]);
            		}
            		printf("\n");
            	}
            }
            mysql_free_result(resposta);
            mysql_close(&conexao);
       }
       else
       {
            printf("Falha de conexao\n");
            printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
       }
      return 0;
}
