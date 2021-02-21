#include "main.h"
using std::string;
using std::to_string;

bool test1 = false;
bool test2 = false;
bool test3 = false;

//Main theme for display.
lv_theme_t * theme_main;

//Auton run page and countdown.
lv_obj_t *page;
lv_obj_t *label_cancel;
lv_obj_t * AutonSelectorButtons;
lv_obj_t * chart;
lv_obj_t *legand;

lv_chart_series_t * NavyLine;
lv_chart_series_t * BlueLine;

lv_chart_series_t * GreenLine;
lv_chart_series_t * LimeLine;

lv_chart_series_t * SilverLine;
lv_chart_series_t * WhiteLine;

lv_chart_series_t * PurpleLine;
lv_chart_series_t * OrangeLine;

//Create a Tab view object
lv_obj_t *tabview;

lv_obj_t *tab1;
lv_obj_t *tab2;
lv_obj_t *tab3;

bool toggleAuton = false;

//Called when cancel auton button is pressed.
static lv_res_t cancel_auton_btn_press(lv_obj_t * btn) {
  //Deletes the page and all child objects.
  lv_obj_del(page);
  toggleAuton = false;

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}


//Called when auton run button is pressed.
static lv_res_t run_auton_btn_press(lv_obj_t * btn) {
  //Creates page.
  page = lv_page_create(tab1, NULL);
  lv_obj_set_size(page, 460, 155);
  lv_obj_align(page, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_page_set_sb_mode(page, LV_SB_MODE_OFF);

  /*Cancel button for run auton page*/
  lv_obj_t * btnCancel = lv_btn_create(page, NULL);
  lv_obj_set_size(btnCancel, 200, 50);
  lv_obj_align(btnCancel, page, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_btn_set_action(btnCancel, LV_BTN_ACTION_CLICK, cancel_auton_btn_press);

  /*Label for cancel auton*/
  lv_obj_t * label = lv_label_create(btnCancel, NULL);
  lv_label_set_text(label, "Cancel Auton");

  /*Displays auton that is about to run*/
  lv_obj_t * label_auton = lv_label_create(page, NULL);
  switch (selectedAuton) {
    case 1: lv_label_set_text(label_auton, "BlueSmall");
      break;
    case 2: lv_label_set_text(label_auton, "BlueSafe");
      break;
    case 3: lv_label_set_text(label_auton, "BlueLarge");
      break;
    case 4: lv_label_set_text(label_auton, "Skills");
      break;
    case 5: lv_label_set_text(label_auton, "RedLarge");
      break;
    case 6: lv_label_set_text(label_auton, "RedSafe");
      break;
    case 7: lv_label_set_text(label_auton, "RedSmall");
      break;
    }
  lv_obj_align(label_auton, btnCancel, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

  /*Countdown until auton is run*/
  label_cancel = lv_label_create(page, NULL);
  lv_label_set_text(label_cancel, "Auton Starting In 5 Seconds.");
  lv_obj_align(label_cancel, label_auton, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

  pros::delay(100);
  toggleAuton = true;


  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

/*Called when a button from the button matrix is pressed*/
static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt) {
  //Changes the selected auton to the corresponding pressed button. Displays on controller.
  if (strcmp(txt, "BSm") == 0) {
    selectedAuton = 1;
  }
  else if (strcmp(txt, "BSaf") == 0) {
    selectedAuton = 2;
  }
  else if (strcmp(txt, "BL") == 0) {
    selectedAuton = 3;
  }
  else if (strcmp(txt, "Skills") == 0) {
    selectedAuton = 4;
  }
  else if (strcmp(txt, "RL") == 0) {
    selectedAuton = 5;
  }
  else if (strcmp(txt, "RSaf") == 0) {
    selectedAuton = 6;
  }
  else if (strcmp(txt, "RSm") == 0) {
    selectedAuton = 7;
  }
  return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

static lv_res_t sw1_action(lv_obj_t *sw) {
  lv_sw_get_state(sw) ? test1 = true : test1 = false;


  return LV_RES_OK;
}


static lv_res_t sw2_action(lv_obj_t *sw) {
  lv_sw_get_state(sw) ? test2 = true : test2 = false;


  return LV_RES_OK;
}


static lv_res_t sw3_action(lv_obj_t *sw) {
  lv_sw_get_state(sw) ? test3 = true : test3 = false;


  return LV_RES_OK;
}


//Text object for displayed variables.
lv_obj_t * txt;

//Create a button descriptor string array
static const char * btnm_map[] = {"BSm", "BSaf", "BL", "Skills", "RL", "RSaf", "RSm", ""};

void runScreen() {
  pros::Task startAuton_TR(startAuton, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "My Task");
  //Sets theme to alien.
  theme_main = lv_theme_alien_init(100, NULL);
  lv_theme_set_current(theme_main);

  tabview = lv_tabview_create(lv_scr_act(), NULL);
  lv_tabview_set_sliding(tabview, false);

  //Add 2 tabs (the tabs are page (lv_page) and can be scrolled
  tab1 = lv_tabview_add_tab(tabview, "Auton Selection");
  lv_page_set_sb_mode(tab1, LV_SB_MODE_OFF);
  tab2 = lv_tabview_add_tab(tabview, "Debug Info");
  lv_page_set_sb_mode(tab2, LV_SB_MODE_OFF);
  tab3 = lv_tabview_add_tab(tabview, "Graph");
  lv_page_set_sb_mode(tab3, LV_SB_MODE_OFF);
  
    chart = lv_chart_create(tab3, NULL);
    lv_chart_set_type(chart, LV_CHART_TYPE_COLUMN);
    
    NavyLine = lv_chart_add_series(chart, LV_COLOR_NAVY);
    BlueLine= lv_chart_add_series(chart, LV_COLOR_BLUE);
     
    GreenLine= lv_chart_add_series(chart, LV_COLOR_GREEN);
    LimeLine= lv_chart_add_series(chart, LV_COLOR_LIME);
    
    SilverLine= lv_chart_add_series(chart, LV_COLOR_SILVER);
    WhiteLine= lv_chart_add_series(chart, LV_COLOR_WHITE);
    
    PurpleLine= lv_chart_add_series(chart, LV_COLOR_PURPLE);
    OrangeLine= lv_chart_add_series(chart, LV_COLOR_ORANGE);
     
    lv_obj_set_size(chart, 280, 155);
    lv_chart_set_div_line_count(chart, 0, 0);
    lv_chart_set_point_count(chart, 1);
    lv_chart_set_range(chart, 0, 50);
    
    legand = lv_label_create(tab3, NULL);
    lv_obj_align(legand, NULL, LV_ALIGN_IN_TOP_MID, 80 , 30);
    lv_label_set_text(legand, "Purple: Intake Motor\n"
                              "Orange: Outake Motor\n"
                              "Silver: Left Roller\n"
                              "White: Right Roller\n"
                              "Blue: Left Drive\n"
                              "Green: Right Drive");

  //Creates box that conatins displayed variables.
  lv_obj_t * box1;
  box1 = lv_cont_create(tab2, NULL);
  lv_obj_set_size(box1, 460, 155);
  lv_obj_set_style(box1, &lv_style_pretty);
  lv_obj_align(box1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

  //Adds the values to the box.
  txt = lv_label_create(box1, NULL);
  lv_obj_align(txt, box1, LV_ALIGN_IN_TOP_LEFT, 10, 1);

  //Create a default button matrix
  AutonSelectorButtons = lv_btnm_create(tab1, NULL);
  lv_btnm_set_map(AutonSelectorButtons, btnm_map);
  lv_btnm_set_toggle(AutonSelectorButtons, true, 0);
  lv_btnm_set_action(AutonSelectorButtons, btnm_action);
  lv_obj_set_size(AutonSelectorButtons, 460, 40);
  lv_obj_align(AutonSelectorButtons, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

  //Copy the button and set toggled state. (The release action is copied too)
  // Auton Run Button.
  lv_obj_t * btn1 = lv_btn_create(tab1, NULL);
  lv_obj_set_size(btn1, 140, 40);
  lv_obj_align(btn1, AutonSelectorButtons, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, run_auton_btn_press);
  //Add a label to the toggled button
  lv_obj_t *label = lv_label_create(btn1, NULL);
  lv_label_set_text(label, "Run");

  //Create switches with labels
  lv_obj_t *sw2 = lv_sw_create(tab1, NULL);
  lv_obj_set_size(sw2, 60, 20);
  lv_obj_align(sw2, AutonSelectorButtons, LV_ALIGN_IN_BOTTOM_MID, 0, 110);
  lv_sw_set_action(sw2, sw2_action);
  lv_obj_t *sw2_label = lv_label_create(tab1, NULL);
  lv_label_set_text(sw2_label, "Test 2");
  lv_obj_align(sw2_label, sw2, LV_ALIGN_OUT_TOP_MID, 0, -10);

  lv_obj_t *sw1 = lv_sw_create(tab1, NULL);
  lv_obj_set_size(sw1, 60, 20);
  lv_obj_align(sw1, sw2, LV_ALIGN_OUT_LEFT_MID, -100, 0);
  lv_sw_set_action(sw1, sw1_action);
  lv_obj_t *sw1_label = lv_label_create(tab1, NULL);
  lv_label_set_text(sw1_label, "Test 1");
  lv_obj_align(sw1_label, sw1, LV_ALIGN_OUT_TOP_MID, 0, -10);

  lv_obj_t *sw3 = lv_sw_create(tab1, NULL);
  lv_obj_set_size(sw3, 60, 20);
  lv_obj_align(sw3, sw2, LV_ALIGN_OUT_RIGHT_MID, 100, 0);
  lv_sw_set_action(sw3, sw3_action);
  lv_obj_t *sw3_label = lv_label_create(tab1, NULL);
  lv_label_set_text(sw3_label, "Test 3");
  lv_obj_align(sw3_label, sw3, LV_ALIGN_OUT_TOP_MID, 0, -10);
  
  
}


double firstLine;
double secondLine;
double thirdLine;
double forthLine;
double fithLine;

void updateLineVariable(int line, double value) {
  switch (line){
    case 1: firstLine = value;
      break;
    case 2: secondLine = value;
      break;
    case 3: thirdLine = value;
      break;
    case 4: forthLine = value;
      break;
    case 5: fithLine = value;
      break;
  }
  lv_label_set_text(txt, (  "Robot Heading: " + to_string(firstLine) + '\n' +
                            "Top Ball Detector: " + to_string(secondLine) + '\n' +
                            "Bottom Ball Detector: " + to_string(thirdLine) + '\n' +
                            "Left Encoder: " + to_string(forthLine) + '\n' +
                            "Right Encoder: " + to_string(fithLine) + '\n' +
                            "Test switches: " + to_string(test1) + " " + to_string(test2) +
                            " " + to_string(test3) + '\n').c_str());
}

bool waitAuton = false;
long currentTime = pros::millis();
void startAuton(void* param) {
  while(true) {
    if (toggleAuton == true) {
      if (!waitAuton) {
        currentTime = pros::millis();
        waitAuton = true;
        printf("Setting time\n");
      }
        lv_label_set_text(label_cancel,   ("Auton Starting In " +
                                          to_string(5 - (((int)pros::millis() - (int)currentTime) / 1000)) +
                                          " Seconds.").c_str());
      if ((currentTime + 5000) < (pros::millis() + 5000) - 5000) {
        toggleAuton = false;
        waitAuton = false;
        lv_obj_del(page);
        printf("Deleted page\n");
        autonomous();
        printf("Starting auton\n");
      }
    }
    else {
      waitAuton = false;
    }

    pros::delay(20);
  }
}

void SetAutonButton(int slot) {
  slot-=1;
  lv_btnm_set_toggle(AutonSelectorButtons, true, slot);
}