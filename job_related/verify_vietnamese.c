bool check_name(char *newName)//为验证方便，验证时候的newName统一转为unicode编码,这样遇到非ascii字符，直接2个2个处理
{
	unsigned int i = 0;
	while(newName[i] != 0 && i < strlen(newName) && i < MAX_NAMESIZE)
	{
		unsigned char temp = newName[i];
		//如果是英文字母和数字
		if( (temp >= '0' && temp <= '9') || (temp >= 'A' && temp <= 'Z') || (temp >= 'a' && temp <= 'z') )
		{
			//是正常的,什么都不做
		}
		else if (temp == 0x1f || temp == 0x01 || temp == 0x1e)
		{
			//越南文的unicode编码范围是00c0-00fd, 0102-01b0, 1ea0-1ef9
			//但00会被当成结束符号,客户端发的时候,会将00加上1f，即合法的越南文编码范围应该是1fc0-1ffd, 0102-01b0, 1ea0-1ef9
			if (!(temp + 1 < strlen(newName) && i < 20))//这里的20意思是,最多允许10个unicode越南文字符,对应的utf-8序列长度最长为30
			{
				return false;
			}
			BYTE next_bit = newName[i+1];
			unsigned short val = (temp << 8) | next_bit;
			if (
					!( (val >= 0x1fc0 && val <= 0x1ffd) || (val >= 0x0102 && val <= 0x01b0) || (val >= 0x1ea0 && val <= 1ef9) )
				)
			{
				return false;
			}
			++i;
		}
		else
		{
			return false;
		}
		++i;
	}
	return true;
}