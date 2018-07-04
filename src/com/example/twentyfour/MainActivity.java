package com.example.twentyfour;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Locale;

import android.os.Bundle;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.graphics.Color;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.SimpleAdapter;
import android.widget.TextView;

public class MainActivity extends Activity {

  private int images[] = null;
  // 透明扑克牌
  private int[] transparent_cards = new int[] { R.drawable.transparent, R.drawable.transparent, R.drawable.transparent,
      R.drawable.transparent, R.drawable.transparent, R.drawable.card_trans_1, R.drawable.card_trans_2, R.drawable.card_trans_3,
      R.drawable.card_trans_4, R.drawable.card_trans_5, R.drawable.card_trans_6, R.drawable.card_trans_7, R.drawable.card_trans_8,
      R.drawable.card_trans_9, R.drawable.card_trans_10, R.drawable.card_trans_11, R.drawable.card_trans_12, R.drawable.card_trans_13 };
  private GridView gridview;
  private Button btn;
  private int[] array = new int[] { -1, -1, -1, -1 };
  private int g_total_points = 24;
  private String strAnswer;

  static void init() {
    System.loadLibrary("getCards"); // 没有 lib 开头
  }

  protected void onResume() {
    super.onResume();
  }

  int exist() {
    for (int i = 0; i < 4; i++) {
      if (array[i] == -1) { // 找到空位置，返回其位置索引
        return i;
      }
    }
    return -1; // 已满
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);

    init();

    images = new int[] { R.drawable.transparent, R.drawable.transparent, R.drawable.transparent, R.drawable.transparent,
        R.drawable.transparent, R.drawable.card_1, R.drawable.card_2, R.drawable.card_3, R.drawable.card_4,
        R.drawable.card_5, R.drawable.card_6, R.drawable.card_7, R.drawable.card_8, R.drawable.card_9,
        R.drawable.card_10, R.drawable.card_11, R.drawable.card_12, R.drawable.card_13 };

    gridview = (GridView) findViewById(R.id.gridview);
    ArrayList<HashMap<String, Object>> lstImageItem = new ArrayList<HashMap<String, Object>>();
    for (int i = 0; i < 18; i++) {
      HashMap<String, Object> map = new HashMap<String, Object>();
      map.put("itemImage", images[i]);
      lstImageItem.add(map);
    }

    SimpleAdapter saImageItems = new SimpleAdapter(this, lstImageItem, // 数据源
        R.layout.item, // 显示布局
        new String[] { "itemImage" /* , "itemText" */ }, new int[] { R.id.image /* , R.id.text */ });
    gridview.setAdapter(saImageItems);

    gridview.setOnItemClickListener(new OnItemClickListener() {
      @Override
      public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
        int index = arg2;
        LinearLayout ll;
        ImageView selectedView;
        ImageView imgView = (ImageView) arg1.findViewById(R.id.image);
        if (index <= 3) { // 点击选好的纸牌 -- 索引从 0 开始
          if (array[index] != -1) { // 已选择，则删除选择的纸牌
            array[index] = -1;
            imgView.setBackgroundColor(Color.TRANSPARENT);
            imgView.setImageResource(R.drawable.transparent);
            strAnswer = "";
            btn.performClick();
          }
        } else if (index >= 5) { // 选择纸牌
          int flag = exist();
          if (-1 != flag) { // 没有满，还可以选择纸牌
            array[flag] = index - 4;
            ll = (LinearLayout) gridview.getChildAt(flag);
            selectedView = (ImageView) ll.findViewById(R.id.image);
            selectedView.setImageResource(transparent_cards[index]);
            selectedView.setBackgroundColor(getResources().getColor(R.color.darkyellow));
          }
          // 如果纸牌满了，开始计算
          if ((array[0] != -1) && (array[1] != -1) && (array[2] != -1) && (array[3] != -1)) {
            strAnswer = JniClient.getCards(array[0], array[1], array[2], array[3], g_total_points);
          }
        }
      }
    });

    btn = (Button) findViewById(R.id.ViewAnswer);
    btn.setOnClickListener(new Button.OnClickListener() {// 创建监听
      public void onClick(View v) {
        TextView tv = (TextView) findViewById(R.id.textViewResult);
        tv.setText(strAnswer);
      }
    });

    String strTitle = String.format(Locale.CHINA, " %d 点游戏", g_total_points);
    setTitle(strTitle); // 设置应用标题
  }

  @Override
  public boolean onCreateOptionsMenu(Menu menu) {
    // Inflate the menu; this adds items to the action bar if it is present.
    getMenuInflater().inflate(R.menu.activity_main, menu);
    return true;
  }

  @Override
  public boolean onOptionsItemSelected(MenuItem item) {
    switch (item.getItemId()) {
    case R.id.menu_settings:
      AlertDialog.Builder builder = new Builder(this);
      builder.setTitle("请选择总点数");
      // 定义单选的选项
      String[] list_items = new String[] { "20点", "21点", "22点", "23点", "24点", "25点", "26点" };
      builder.setSingleChoiceItems(list_items, -1, new OnClickListener() {
        @Override
        public void onClick(DialogInterface dialog, int which) {
          g_total_points = 20 + which;
          String strTitle = String.format(Locale.CHINA, " %d 点游戏", g_total_points);
          setTitle(strTitle); // 重新开始
          TextView tv = (TextView) findViewById(R.id.textViewResult);
          tv.setText("");
          array = new int[] { -1, -1, -1, -1 };
          for (int i = 0; i < 4; i++) {
            LinearLayout ll = (LinearLayout) gridview.getChildAt(i);
            ImageView imgView = (ImageView) ll.findViewById(R.id.image);
            imgView.setBackgroundColor(Color.TRANSPARENT);
            imgView.setImageResource(R.drawable.transparent);
          }
          strAnswer = "";
          dialog.dismiss();
        }
      });
      builder.setNegativeButton("取消", new OnClickListener() {
        @Override
        public void onClick(DialogInterface dialog, int which) {

        }
      });
      builder.show();
      return true;
    default:
      return false;
    }
  }
}