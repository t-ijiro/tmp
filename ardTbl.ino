#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef enum{
  HWTEST_STATE_SEL_MENU,
  HWTEST_STATE_EXEC_TEST
}HWTEST_STATE_t;

typedef struct HWTEST_menu_tbl_t{
  char *p_command;
  char *p_command_title;
  char *p_prompt;
  char *p_illegal;
  void (*p_func)(void *);
  struct HWTEST_menu_tbl_t *p_tbl;
  char *p_menu_title;
}HWTEST_menu_tbl_t, *pHWTEST_menu_tbl_t;

typedef struct{
  pHWTEST_menu_tbl_t p_current_tbl;
  pHWTEST_menu_tbl_t p_current_menu;
  HWTEST_STATE_t state;
}HWTEST_INFO_t;

#define RCV_BUF_SIZE 64
typedef struct{
  char buf[RCV_BUF_SIZE];
  uint8_t count;
}rcv_buf_info_t;

HWTEST_INFO_t hwtest_info;
rcv_buf_info_t rcv_buf_info;

void dummy1(void *a)
{
  Serial.println("");
  Serial.println("dummy1 exec");
show(a);
}

void dummy2(void *a)
{
   Serial.println("");
  Serial.println("dummy2 exec");
show(a);
}
void dummy3(void *a)
{
   Serial.println("");
  Serial.println("dummy3 exec");
show(a);
}
void dummy4(void *a)
{
   Serial.println("");
  Serial.println("dummy4 exec");
show(a);
}
void dummy5(void *a)
{
   Serial.println("");
  Serial.println("dummy5 exec");
show(a);
}
void dummy6(void *a)
{
   Serial.println("");
  Serial.println("dummy6 exec");
show(a);
}
void dummy7(void *a)
{
   Serial.println("");
  Serial.println("dummy7 exec");
show(a);
}
void dummy8(void *a)
{
   Serial.println("");
  Serial.println("dummy8 exec");
show(a);
}
void dummy9(void *a)
{
   Serial.println("");
  Serial.println("dummy9 exec");
show(a);
}
void dummy10(void *a)
{
   Serial.println("");
  Serial.println("dummy10 exec");
show(a);
}
void dummy11(void *a)
{
   Serial.println("");
Serial.println("dummy11 exec");
  show(a);
}

void dummy12(void *a)
{
   Serial.println("");
Serial.println("dummy12 exec");
  show(a);
}

void HWTEST_illegal()
{
   Serial.println("");
Serial.println("dummy ille exec");
 // show(a);
}

void show(void *a)
{
  pHWTEST_menu_tbl_t p_tmp_tbl = (pHWTEST_menu_tbl_t)a;
  int i;

  Serial.println("");
  Serial.println("");

 i = 0;
  for(;;)
  {
    if(p_tmp_tbl[i].p_command == NULL)
    {
      break;
    }

    i++;
  }

  pHWTEST_menu_tbl_t p_tmp_menu = &p_tmp_tbl[i - 1];

  p_tmp_tbl = p_tmp_menu->p_tbl;

  Serial.println(p_tmp_menu->p_menu_title);

  i = 0;

  for(;;)
  {
    if(p_tmp_tbl[i].p_command == NULL)
    {
      break;
    }

    if(p_tmp_tbl[i].p_command_title != NULL)
    {
      Serial.print(" ");
      Serial.println(p_tmp_tbl[i].p_command_title);
    }
    i++;
  }

  Serial.print(" ");
  Serial.print(p_tmp_menu->p_prompt);
  hwtest_info.state = HWTEST_STATE_SEL_MENU;
}


HWTEST_menu_tbl_t hwtest_menu_tbl[3][16] = {
  {
    {"1", "1.DIPSW", ">", ">", dummy1, hwtest_menu_tbl[0], "***** HW試験メニュー *****"},
    {"2", "2.EEPROMアクセス", ">", ">", dummy2, hwtest_menu_tbl[0], "***** HW試験メニュー *****"},
    {"3", "3.BU-6558bアクセス", ">", ">", show, hwtest_menu_tbl[1], "***** BU-6553bアクセス *****"},
    {"4", "4.SPARE1_OUT", ">", ">", dummy4, hwtest_menu_tbl[0], "***** HW試験メニュー *****"},
    {"5", "5.SPARE2_OUT", ">", ">", dummy5, hwtest_menu_tbl[0], "***** HW試験メニュー *****"},
    {"6", "6.SPARE_IN", ">", ">", dummy6, hwtest_menu_tbl[0], "***** HW試験メニュー *****"},
    {"7", "7.シリアル通信", ">", ">", dummy7, hwtest_menu_tbl[0], "***** HW試験メニュー *****"},
    {"8", "8.R/Wコマンド", ">", ">", dummy8, hwtest_menu_tbl[0], "***** HW試験メニュー *****"},
    {"-1", NULL,    ">", ">", show, hwtest_menu_tbl[0], "***** HW試験メニュー *****"},
    {NULL, NULL,    NULL, NULL, NULL, NULL, NULL}
  },
  {
    {"1", "1.RTアドレス", ">", ">", dummy9, hwtest_menu_tbl[1], "***** HW試験メニュー/BU-6553bアクセス *****"},
    {"2", "2.レジスタ", ">", ">", dummy10, hwtest_menu_tbl[1], "***** HW試験メニュー/BU-6553bアクセス *****"},
    {"3", "3.メモリ", ">", ">", dummy11, hwtest_menu_tbl[1], "***** HW試験メニュー/BU-6553bアクセス *****"},
    {"0",  "0.戻る",    ">", ">", show, hwtest_menu_tbl[0], "***** HW試験メニュー *****"},
    {"-1", NULL,      ">", ">", show, hwtest_menu_tbl[1], "***** HW試験メニュー/BU-6553bアクセス *****"},
    {NULL, NULL,    NULL, NULL, NULL, NULL, NULL}
  },
  {
    {NULL,  NULL,    ">", "?", dummy12, hwtest_menu_tbl[0], "メニュー"}
  }

};

uint8_t HWTEST_getline(rcv_buf_info_t *p_rcv_buf_info)
{
  uint8_t result = 0;
  char *p_buf = p_rcv_buf_info->buf;
  char *p_end;

  if(Serial.available())
  {
    char ch = Serial.read();

    Serial.print(ch);

    if(ch == '\n')
    {
      // LFは無視
    }
    else if(ch == '\b')
    {
      if(p_rcv_buf_info->count > 0)
      {
        p_rcv_buf_info->count--;
      }
    }
    else if(ch == '\r')
    {
      result = 1;
    }
    else
    {
      if(p_rcv_buf_info->count < RCV_BUF_SIZE - 1)
      {
        p_buf[p_rcv_buf_info->count++] = ch;
      }
    }
  }

  return result;
}

char * HWTEST_skip_spaces(char *p_buf)
{
  if(!p_buf)
  {
    return NULL;
  }

  while(*p_buf == ' ' && *p_buf != '\0')
  {
    p_buf++;
  }
  return p_buf;
}

void HWTEST_command_proc(rcv_buf_info_t *p_rcv_buf_info)
{
  long user_10base_in;
  char *p_buf = p_rcv_buf_info->buf;
  uint8_t rcv_count = p_rcv_buf_info->count;
  char *p_end;

  if(rcv_count == 0)
  {
    user_10base_in = -1;
    //Serial.println("user empty input");
  }
  else
  {
    p_buf = HWTEST_skip_spaces(p_buf);

    user_10base_in = strtol(p_buf, &p_end, 10);

    if(p_end == p_buf && *p_end == '\0')
    {
      user_10base_in = -1;
    }
    else
    {
      p_end = HWTEST_skip_spaces(p_end);

      if(*p_end != '\0')
      {
        Serial.println("!! 10進数で入力してください !!");
        show((pHWTEST_menu_tbl_t)hwtest_info.p_current_tbl);
        return;
      }
    }
  }

    pHWTEST_menu_tbl_t p_tmp_tbl = hwtest_info.p_current_tbl;

    uint8_t i = 0;

    for(;;)
    {
      if(p_tmp_tbl[i].p_command == NULL)
      {
        Serial.println("!! 存在しないコマンドです !!");
        show((pHWTEST_menu_tbl_t)hwtest_info.p_current_tbl);
        return;
      }

      long cmd_10base = strtol(p_tmp_tbl[i].p_command, NULL, 10);

      if(cmd_10base == user_10base_in)
      {
        hwtest_info.p_current_tbl = p_tmp_tbl[i].p_tbl;
        hwtest_info.p_current_menu = &p_tmp_tbl[i];
        hwtest_info.state = HWTEST_STATE_EXEC_TEST;
        return;
      }

      i++;
    }

    
}

void HWTEST_sel_menu(void)
{
  if(HWTEST_getline(&rcv_buf_info))
  {
    HWTEST_command_proc(&rcv_buf_info);
    memset(&rcv_buf_info, 0, sizeof(rcv_buf_info));
  }
}

void HWTEST_exec_test(void)
{
  pHWTEST_menu_tbl_t p_tmp_tbl = hwtest_info.p_current_tbl;
  pHWTEST_menu_tbl_t p_tmp_menu = hwtest_info.p_current_menu;
  p_tmp_menu->p_func((pHWTEST_menu_tbl_t)p_tmp_tbl);
}

void HWTEST_main(void)
{
  HWTEST_STATE_t state = hwtest_info.state;

  switch(state)
  {
    case HWTEST_STATE_SEL_MENU :
      HWTEST_sel_menu();
      break;
    case HWTEST_STATE_EXEC_TEST :
      HWTEST_exec_test();
      break;
    default :
      break;
  }

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hwtest_info.p_current_tbl = hwtest_menu_tbl[0];
  hwtest_info.state = HWTEST_STATE_SEL_MENU;

}

void loop() {

  HWTEST_main();
 
}
いったん置いておくだけ