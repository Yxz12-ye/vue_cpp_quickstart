<template>
  <div class="hero">
    <div class="card">
      <img src="@/assets/logo.svg" class="logo" alt="logo" />
      <div class="content">
        <h1>Vue + Vite + Drogon</h1>
        <p class="subtitle">混合 C++ 后端 与 Vue 前端 快速起步模板</p>
        <p class="description">轻松连接后端 API，立即查看返回消息。</p>

        <div class="actions">
          <CustomButton type="primary" @click="fetchFromBack" :disabled="loading">
            {{ loading ? '请求中...' : '从后端获取消息' }}
          </CustomButton>
          <CustomButton type="ghost" @click="addLocalMessage">本地问候</CustomButton>
          <CustomButton type="danger" @click="clearHistory" v-if="messageHistory.length > 0">清空历史</CustomButton>
        </div>

        <transition name="fade">
          <div v-if="messageHistory.length > 0" class="msg-history">
            <div class="history-header">
              <strong>消息历史 ({{ messageHistory.length }})</strong>
            </div>
            <div v-for="(msg, index) in messageHistory" :key="index" class="msg-card" :class="msg.type">
              <div class="msg-meta">
                <span class="msg-type">{{ getTypeLabel(msg.type) }}</span>
                <span class="msg-time">{{ msg.timestamp }}</span>
              </div>
              <div class="msg-content">{{ msg.content }}</div>
            </div>
          </div>
        </transition>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue';
import CustomButton from './CustomButton.vue';
import axios from 'axios';

const loading = ref(false);
const messageHistory = ref([]);

const getCurrentTime = () => {
  const now = new Date();
  return now.toLocaleTimeString('zh-CN', { hour12: false });
};

const getTypeLabel = (type) => {
  const labels = {
    success: '✓ 成功',
    error: '✗ 错误',
    local: 'i 本地'
  };
  return labels[type] || type;
};

const addMessage = (content, type = 'success') => {
  messageHistory.value.unshift({
    content,
    type,
    timestamp: getCurrentTime()
  });
};

const addLocalMessage = () => {
  addMessage('本地问候：你好！', 'local');
};

const fetchFromBack = async () => {
  loading.value = true;
  try {
    const response = await axios.get('/test/v1/testCtrl/test');
    const msg = response.data && response.data.msg ? response.data.msg : JSON.stringify(response.data);
    addMessage(msg, 'success');
  } catch (error) {
    let errorMsg;
    if (error && error.response && error.response.data && error.response.data.message) {
      errorMsg = '错误：' + error.response.data.message;
    } else if (error && error.message) {
      errorMsg = '错误：' + error.message;
    } else {
      errorMsg = '未知错误';
    }
    addMessage(errorMsg, 'error');
  } finally {
    loading.value = false;
  }
};

const clearHistory = () => {
  messageHistory.value = [];
};
</script>

<style scoped>
:root {
  --bg1: #071028;
  --bg2: #0b1830;
  --card: rgba(255, 255, 255, 0.03);
  --accent: #7c3aed;
  --muted: #98a6bf;
  --success: #10b981;
  --error: #ef4444;
  --local: #3b82f6;
}

.hero {
  min-height: 100vh;
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 2rem 1rem;
  flex-direction: column;
  gap: 1rem;
}

@media (min-width: 1024px) {
  .hero {
    min-height: auto;
    padding: 2rem;
  }
}

.card {
  display: flex;
  gap: 1.5rem;
  align-items: center;
  background: linear-gradient(180deg, rgba(255, 255, 255, 0.02), rgba(255, 255, 255, 0.01));
  border-radius: 14px;
  padding: 1.75rem;
  box-shadow: 0 10px 30px rgba(2, 6, 23, 0.6);
  max-width: 920px;
  width: 100%;
}

.logo {
  width: 88px;
  height: 88px;
  filter: drop-shadow(0 8px 20px rgba(124, 58, 237, 0.18));
}

.content {
  flex: 1;
}

h1 {
  margin: 0 0 0.25rem 0;
  font-size: 1.9rem;
  letter-spacing: -0.02em;
}

.subtitle {
  margin: 0 0 0.6rem 0;
  color: var(--muted);
}

.description {
  margin: 0 0 1rem 0;
  color: #c7d3ee;
}

.actions {
  display: flex;
  gap: 0.75rem;
  margin-bottom: 0.75rem;
  flex-wrap: wrap;
}

.msg-history {
  margin-top: 1rem;
  max-height: 320px;
  overflow-y: auto;
}

.history-header {
  margin-bottom: 0.75rem;
  padding-bottom: 0.5rem;
  border-bottom: 1px solid rgba(255, 255, 255, 0.1);
  color: var(--muted);
  font-size: 0.9rem;
}

.msg-card {
  margin-bottom: 0.75rem;
  background: rgba(255, 255, 255, 0.02);
  border-left: 4px solid var(--accent);
  padding: 0.72rem 1rem;
  border-radius: 8px;
  color: #e6eef8;
  transition: transform 0.2s, box-shadow 0.2s;
}

.msg-card:hover {
  transform: translateX(4px);
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.3);
}

.msg-card.success {
  border-left-color: var(--success);
}

.msg-card.error {
  border-left-color: var(--error);
}

.msg-card.local {
  border-left-color: var(--local);
}

.msg-meta {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 0.5rem;
  font-size: 0.85rem;
}

.msg-type {
  font-weight: 500;
}

.msg-card.success .msg-type {
  color: var(--success);
}

.msg-card.error .msg-type {
  color: var(--error);
}

.msg-card.local .msg-type {
  color: var(--local);
}

.msg-time {
  color: var(--muted);
  font-size: 0.8rem;
}

.msg-content {
  word-break: break-word;
  line-height: 1.5;
}

.fade-enter-active,
.fade-leave-active {
  transition: opacity .35s;
}

.fade-enter-from,
.fade-leave-to {
  opacity: 0;
}

.msg-history::-webkit-scrollbar {
  width: 6px;
}

.msg-history::-webkit-scrollbar-track {
  background: rgba(255, 255, 255, 0.05);
  border-radius: 3px;
}

.msg-history::-webkit-scrollbar-thumb {
  background: rgba(255, 255, 255, 0.2);
  border-radius: 3px;
}

.msg-history::-webkit-scrollbar-thumb:hover {
  background: rgba(255, 255, 255, 0.3);
}

@media (max-width: 640px) {
  .card {
    flex-direction: column;
    text-align: center;
  }

  .logo {
    margin-bottom: 0.5rem;
  }

  .actions {
    justify-content: center;
  }
}
</style>