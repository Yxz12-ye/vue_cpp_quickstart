<template>
  <CustomButton type="default" @click="fetchFromBack">click me</CustomButton>
  <br>
  <label>{{ myMsg }}</label>
</template>

<script setup>
import { handleError, ref } from 'vue';
import CustomButton from './CustomButton.vue';
import axios from 'axios';

let myMsg = ref("hello!")
const click_type = ["get_msg", "set_msg"]
const fetchFromBack = async () => {

  console.log("hello")

  try {
    const response = await axios.get('/api/test')
    const msg = response.data
    console.log(msg["msg"]);
    myMsg.value = msg['msg']

  } catch (error) { // 这里是 error
    // error.value = err.message // ❌ 应该用 error
    // console.error('获取失败:', err) // ❌ 应该用 error

    // ✅ 正确的做法
    // 如果 error.value 是一个响应式变量，例如 ref()
    if (error.response && error.response.data && error.response.data.message) {
      // 如果后端返回了错误信息
      // error.value = error.response.data.message;
      console.error('获取失败:', error.response.data.message);
    } else if (error.message) {
      // error.value = error.message;
      console.error('获取失败:', error.message);
    } else {
      // error.value = '未知错误';
      console.error('获取失败:', error);
    }
  }

}
</script>