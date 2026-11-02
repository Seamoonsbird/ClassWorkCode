#include <stdio.h>
#include <string.h>

#define Max_len 301
#define Max_words 100
#define Max_word_len 51
//转换大小写
void to_lower_case(char* str){
	while(*str!='\0'&&*str<='Z'&&*str>='A'){
		*str = *str+'a'-'A';
		str++;
	}
} 

//判断是字母还是符号
int is_alpha(char c){
	if(c>='a'&&c<='z'){
		return 1;
	}else{
		return 0;
	}
} 

//判断是否存在
int is_word_exist(char only_words[][Max_word_len],int count,char*word){
	for(int i=0;i<count;i++){
		if(strcmp(only_words[i],word)==0){
			return 1;
		}
	}
	return 0;
} 


int main(){
	char only_words[Max_words][Max_word_len];
	char str[Max_len];
	char temp_word[Max_word_len]={0};

	//读取并存入 	
	fgets(str, Max_len, stdin);
	str[strcspn(str,"\n")] = '\0';

    
    //转换
	to_lower_case(str);

	//遍历字符串
	char* p=str;
	int i=0;
	int word_count=0;
	
	while(*p!='\0'){
		while(*p!='\0'&&is_alpha(*p)==0){
			p++;
		} 
		if(*p=='\0'){
			break;
		}
		
		while(*p!='\0'&&is_alpha(*p)==1){
			temp_word[i]=*p;
			i++;
			p++;
		}
		temp_word[i]='\0';
	
		if(!is_word_exist(only_words,word_count,temp_word)){
			strcpy(only_words[word_count],temp_word);
			word_count++;
		}
		for(int j=0;temp_word[j]!='\0';j++){
			temp_word[j]='\0';
		}
		i=0;
	}

    printf("%d",word_count);
	return 0;
}