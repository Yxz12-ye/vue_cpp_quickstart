<script setup>
import HelloWorld from './components/HelloWorld.vue';
import AppIntro from './components/AppIntro.vue';
</script>

<template>
  <HelloWorld />
  <AppIntro />
  <footer class="app-footer">
    Built with ❤️ — Vue + Vite + Drogon
  </footer>
</template>

<style scoped>
.app-footer {
  text-align: center;
  padding: 1rem;
  color: var(--muted);
  font-size: 0.9rem;
}
</style>