<template>
  <div class="intro-container">
    <div class="intro-card">
      <h2>关于本项目</h2>
      <p class="lead">一个现代化的全栈开发模板</p>

      <div class="feature-list">
        <div class="feature-item">
          <div class="feature-icon">⚡</div>
          <div class="feature-content">
            <h3>Vue 3 + Vite</h3>
            <p>使用最新的前端技术栈，提供极速的开发体验</p>
          </div>
        </div>

        <div class="feature-item">
          <div class="feature-icon">🚀</div>
          <div class="feature-content">
            <h3>Drogon 后端</h3>
            <p>高性能 C++ Web 框架，支持 HTTP/WebSocket</p>
          </div>
        </div>

        <div class="feature-item">
          <div class="feature-icon">🔧</div>
          <div class="feature-content">
            <h3>快速开发</h3>
            <p>开箱即用的配置，专注于业务逻辑实现</p>
          </div>
        </div>
      </div>

      <div class="tech-stack">
        <h4>技术栈</h4>
        <div class="tech-tags">
          <span class="tech-tag">Vue 3</span>
          <span class="tech-tag">Vite</span>
          <span class="tech-tag">Drogon</span>
          <span class="tech-tag">C++17</span>
          <span class="tech-tag">CMake</span>
          <span class="tech-tag">spdlog</span>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup>
// 这是一个纯展示组件，不需要额外的逻辑
</script>

<style scoped>
.intro-container {
  display: flex;
  align-items: center;
  justify-content: center;
  min-height: 100vh;
  padding: 2rem 1rem;
}

@media (min-width: 1024px) {
  .intro-container {
    min-height: auto;
    padding: 2rem;
  }
}

.intro-card {
  background: linear-gradient(180deg, rgba(255, 255, 255, 0.02), rgba(255, 255, 255, 0.01));
  border-radius: 14px;
  padding: 2rem;
  box-shadow: 0 10px 30px rgba(2, 6, 23, 0.6);
  max-width: 480px;
  width: 100%;
  color: #e6eef8;
}

h2 {
  margin: 0 0 0.5rem 0;
  font-size: 2rem;
  letter-spacing: -0.02em;
  color: #e6eef8;
}

.lead {
  margin: 0 0 2rem 0;
  color: var(--muted);
  font-size: 1.1rem;
}

.feature-list {
  display: flex;
  flex-direction: column;
  gap: 1.25rem;
  margin-bottom: 2rem;
}

.feature-item {
  display: flex;
  gap: 1rem;
  align-items: flex-start;
}

.feature-icon {
  font-size: 1.75rem;
  line-height: 1;
  flex-shrink: 0;
  width: 40px;
  height: 40px;
  display: flex;
  align-items: center;
  justify-content: center;
  background: rgba(124, 58, 237, 0.1);
  border-radius: 10px;
}

.feature-content h3 {
  margin: 0 0 0.25rem 0;
  font-size: 1.1rem;
  color: #e6eef8;
}

.feature-content p {
  margin: 0;
  color: var(--muted);
  font-size: 0.95rem;
  line-height: 1.5;
}

.tech-stack h4 {
  margin: 0 0 0.75rem 0;
  font-size: 1rem;
  color: var(--muted);
  text-transform: uppercase;
  letter-spacing: 0.05em;
}

.tech-tags {
  display: flex;
  flex-wrap: wrap;
  gap: 0.5rem;
}

.tech-tag {
  background: rgba(124, 58, 237, 0.15);
  color: #c7d3ee;
  padding: 0.4rem 0.75rem;
  border-radius: 6px;
  font-size: 0.85rem;
  border: 1px solid rgba(124, 58, 237, 0.2);
  transition: all 0.2s;
}

.tech-tag:hover {
  background: rgba(124, 58, 237, 0.25);
  border-color: rgba(124, 58, 237, 0.3);
}
</style>