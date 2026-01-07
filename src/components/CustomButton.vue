<template>
    <button :class="buttonClass" @click="handleClick" :disabled="disabled || loading">
        <span class="vue-button__content">
            <span v-if="loading" class="vue-button__loader"></span>
            <span v-else-if="icon && iconPosition === 'left'" class="vue-button__icon-left">
                <span class="icon">{{ getIconSymbol(icon) }}</span>
            </span>

            <span v-if="$slots.default" class="vue-button__text">
                <slot></slot>
            </span>

            <span v-if="icon && iconPosition === 'right' && !loading" class="vue-button__icon-right">
                <span class="icon">{{ getIconSymbol(icon) }}</span>
            </span>
        </span>
    </button>
</template>

<script setup>
import { computed } from 'vue'

const props = defineProps({
    type: {
        type: String,
        default: 'default',
        validator: (value) => ['default', 'primary', 'success', 'warning', 'danger', 'info'].includes(value)
    },
    size: {
        type: String,
        default: 'medium',
        validator: (value) => ['small', 'medium', 'large'].includes(value)
    },
    variant: {
        type: String,
        default: 'solid',
        validator: (value) => ['solid', 'outline', 'ghost', 'text'].includes(value)
    },
    icon: {
        type: String,
        default: ''
    },
    iconPosition: {
        type: String,
        default: 'left',
        validator: (value) => ['left', 'right'].includes(value)
    },
    disabled: {
        type: Boolean,
        default: false
    },
    loading: {
        type: Boolean,
        default: false
    },
    rounded: {
        type: Boolean,
        default: false
    }
})

const emit = defineEmits(['click'])

const buttonClass = computed(() => ({
    'vue-button': true,
    [`vue-button--${props.type}`]: true,
    [`vue-button--${props.size}`]: true,
    [`vue-button--${props.variant}`]: true,
    'vue-button--disabled': props.disabled,
    'vue-button--loading': props.loading,
    'vue-button--rounded': props.rounded,
    'vue-button--icon-only': props.icon && !useSlots().default
}))

const handleClick = (e) => {
    if (!props.disabled && !props.loading) {
        emit('click', e)
    }
}

const getIconSymbol = (iconName) => {
    const iconMap = {
        'download': '↓',
        'check-circle': '✓',
        'trash': '×',
        'alert-triangle': '!',
        'plus': '+',
        'search': '🔍',
        'heart': '♥'
    }
    return iconMap[iconName] || '○'
}
</script>

<style scoped>
.vue-button {
    display: inline-flex;
    align-items: center;
    justify-content: center;
    border: none;
    outline: none;
    cursor: pointer;
    font-weight: 500;
    transition: all 0.3s ease;
    white-space: nowrap;
    user-select: none;
    position: relative;
    overflow: hidden;
    font-family: inherit;
}

.vue-button:active {
    transform: translateY(1px);
}

.vue-button__content {
    display: flex;
    align-items: center;
    justify-content: center;
    gap: 8px;
}

.vue-button__loader {
    width: 16px;
    height: 16px;
    border-radius: 50%;
    border: 2px solid rgba(255, 255, 255, 0.3);
    border-top-color: white;
    animation: spin 0.8s linear infinite;
}

@keyframes spin {
    to {
        transform: rotate(360deg);
    }
}

/* 按钮类型样式 */
.vue-button--default {
    background-color: #f8f9fa;
    color: #212529;
    border: 1px solid #dee2e6;
}

.vue-button--primary {
    background-color: #3498db;
    color: white;
}

.vue-button--success {
    background-color: #2ecc71;
    color: white;
}

.vue-button--warning {
    background-color: #f39c12;
    color: white;
}

.vue-button--danger {
    background-color: #e74c3c;
    color: white;
}

.vue-button--info {
    background-color: #95a5a6;
    color: white;
}

/* 按钮尺寸 */
.vue-button--small {
    padding: 6px 12px;
    font-size: 0.875rem;
    border-radius: 4px;
}

.vue-button--medium {
    padding: 10px 20px;
    font-size: 1rem;
    border-radius: 6px;
}

.vue-button--large {
    padding: 14px 28px;
    font-size: 1.125rem;
    border-radius: 8px;
}

/* 按钮变体 */
.vue-button--outline {
    background-color: transparent;
    border: 2px solid;
}

.vue-button--outline.vue-button--primary {
    color: #3498db;
    border-color: #3498db;
}

.vue-button--outline.vue-button--success {
    color: #2ecc71;
    border-color: #2ecc71;
}

.vue-button--outline.vue-button--warning {
    color: #f39c12;
    border-color: #f39c12;
}

.vue-button--outline.vue-button--danger {
    color: #e74c3c;
    border-color: #e74c3c;
}

.vue-button--outline.vue-button--info {
    color: #95a5a6;
    border-color: #95a5a6;
}

.vue-button--outline.vue-button--default {
    color: #495057;
    border-color: #ced4da;
}

.vue-button--ghost {
    background-color: transparent;
    border: none;
}

.vue-button--ghost.vue-button--primary {
    color: #3498db;
}

.vue-button--ghost.vue-button--success {
    color: #2ecc71;
}

.vue-button--ghost.vue-button--warning {
    color: #f39c12;
}

.vue-button--ghost.vue-button--danger {
    color: #e74c3c;
}

.vue-button--ghost.vue-button--info {
    color: #95a5a6;
}

.vue-button--ghost.vue-button--default {
    color: #6c757d;
}

.vue-button--text {
    background-color: transparent;
    border: none;
    color: inherit;
}

.vue-button--text:hover {
    background-color: rgba(0, 0, 0, 0.05);
}

/* 圆角按钮 */
.vue-button--rounded {
    border-radius: 50px !important;
}

/* 禁用状态 */
.vue-button--disabled,
.vue-button:disabled {
    opacity: 0.6;
    cursor: not-allowed;
    transform: none !important;
}

/* 悬停效果 */
.vue-button:not(.vue-button--disabled):not(.vue-button--text):hover {
    filter: brightness(110%);
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
}

.vue-button--outline:not(.vue-button--disabled):hover {
    background-color: rgba(0, 0, 0, 0.05);
}

.vue-button--ghost:not(.vue-button--disabled):hover {
    background-color: rgba(0, 0, 0, 0.05);
}

/* 图标 */
.vue-button__icon-left,
.vue-button__icon-right {
    display: flex;
    align-items: center;
}
</style>